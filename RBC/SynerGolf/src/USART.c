#include "USART.h"
#include "data.h"
#include "LED.h"

extern volatile Data globalData;

void initializeUSART()
{
	GPIO_InitTypeDef usart_gpio;

	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;


	usart_gpio.GPIO_Pin = RX3_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX3_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX3_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX3_GPIO, &usart_gpio);


	USART_InitTypeDef usart_conf;

	usart_conf.USART_BaudRate = 9600; // hc05
	usart_conf.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_conf.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	usart_conf.USART_Parity=USART_Parity_No;
	usart_conf.USART_StopBits=USART_StopBits_1;
	usart_conf.USART_WordLength=USART_WordLength_8b;


	USART_Cmd(USART3, ENABLE);

	USART_Init(USART3, &usart_conf);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART3_IRQn);
}

void sendLineFeed(USART_TypeDef *USARTx)
{
	// Send line feed
	while ((USARTx->SR & USART_FLAG_TXE) == RESET) {}
	USARTx->DR = 0x0A;
}

void USARTInterrupt(USART_TypeDef *USARTx)
{
	static uint8_t address = 0;
	static uint8_t dir = 0;
	static uint8_t data_h = 0;

	/* RXNE handler */
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{
		globalData.communication_safety = 1;
		//Disable interrupt until all data is received
		USARTx->CR1 &= ~USART_CR1_RXNEIE;

		uint8_t data = USARTx->DR;

		if(data == 0xFF && globalData.bStartByteReceived == 0) // start command
		{
			globalData.bStartByteReceived = 1;
		}
		else if( globalData.bStartByteReceived == 1 )
		{
			address = (data&0b11110000)>>4;
			dir = (data&0b00001100)>>2;
			data_h = data&0b00000011;

			switch(address)
			{
				case 1:
				case 2:
				case 3:
					globalData.bStartByteReceived = 2;
					break;

				case 4: //left
					globalData.putterRequest = dPutterRequest_left;
					globalData.bStartByteReceived = 0;
					break;

				case 5://right
					globalData.putterRequest = dPutterRequest_right;
					globalData.bStartByteReceived = 0;
					break;

				case 6://stop
					globalData.putterRequest = dPutterRequest_stop;
					globalData.bStartByteReceived = 0;
					break;

				case 7://putt
					globalData.putterRequest = dPutterRequest_putt;
					globalData.bStartByteReceived = 0;
					break;

				case 8://calibrate
					globalData.stepsCounter = 0;
					globalData.bStartByteReceived = 0;
					break;

				default:
					break;
			}
		}
		else if(globalData.bStartByteReceived == 2)
		{
			switch(address)
			{
				case 1:
				case 2:
				case 3:
					setDCMotor(address, (data_h<<8)+data, dir);
					break;

				default:
					break;
			}
			globalData.bStartByteReceived = 0;
		}

		//Enable receive interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}
	else
	{
		// error occurred start interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
		return;
	}
}

void USART3_IRQHandler(void)
{
	USARTInterrupt(USART3);
}
