#include "USART.h"
#include "data.h"
#include "LED.h"

extern volatile Data globalData;

void initializeUSART()
{
	/*
	 * PIN configuration
	 */
	GPIO_InitTypeDef usart_gpio;

	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	/*usart_gpio.GPIO_Pin = RX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX_GPIO, &usart_gpio);*/

	usart_gpio.GPIO_Pin = RX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX2_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX2_GPIO, &usart_gpio);

	/*
	 * USART configuration
	 */
	//USART_Cmd(USART1, ENABLE);

	USART_InitTypeDef usart_conf;

	// usart_conf.USART_BaudRate=9600; HC-05
	usart_conf.USART_BaudRate = 9600; // BTM 222
	usart_conf.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_conf.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	usart_conf.USART_Parity=USART_Parity_No;
	usart_conf.USART_StopBits=USART_StopBits_1;
	usart_conf.USART_WordLength=USART_WordLength_8b;

	//USART_Init(USART1, &usart_conf);
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	//NVIC_EnableIRQ(USART1_IRQn);

	/*
	 * USART2
	 */

	USART_Cmd(USART2, ENABLE);

	USART_Init(USART2, &usart_conf);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART2_IRQn);
}

void sendLineFeed(USART_TypeDef *USARTx)
{
	// Send line feed
	while ((USARTx->SR & USART_FLAG_TXE) == RESET) {}
	USARTx->DR = 0x0A;
}

void USARTInterrupt(USART_TypeDef *USARTx)
{
	/* RXNE handler */
	if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
	{
		globalData.communication_safety = 1;
		//LED4_GPIO->ODR ^= LED4_PIN;
		//Disable interrupt until all data is received
		USARTx->CR1 &= ~USART_CR1_RXNEIE;

		//LED2_ON;
		/*
		 * Proceed commands
		 */

		uint8_t data = USARTx->DR;

		if (data == 0xFF) // start command
		{
			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;

			uint8_t address = (data&0b11110000)>>4;
			uint8_t dir = (data&0b00001100)>>2;
			uint8_t data_h = data&0b00000011;

			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;


			if(address==1||address==2||address==3){
				setDCMotor(address, (data_h<<8)+data, dir);
			}

			else if(address==4){
				uint16_t steps = (data_h<<8)+data;

				while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
				data = USARTx->DR;

				setStepperPosition(data, steps, dir);
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

	else if(USART_GetITStatus(USARTx, USART_IT_TXE) != RESET)
	{
		//Disable transmit interrupt
		USARTx->CR1 &= ~(USART_CR1_TXEIE);

		USARTx->DR = globalData.battery_level;
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = 'b';
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = 'c';

		//Enable receive interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}
}

/*void USART1_IRQHandler(void)
{
	USARTInterrupt(USART1);
}*/

void USART2_IRQHandler(void)
{
	USARTInterrupt(USART2);
}
