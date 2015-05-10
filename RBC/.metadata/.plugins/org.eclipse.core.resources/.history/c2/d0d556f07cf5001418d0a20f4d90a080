#include "USART.h"
#include "data.h"

extern volatile Data globalData;

void initializeUSART()
{
	/*
	 * PIN configuration
	 */
	GPIO_InitTypeDef usart_gpio;

	usart_gpio.GPIO_Speed = GPIO_Speed_50MHz;
	usart_gpio.GPIO_Pin = RX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = RX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

	GPIO_Init(RX2_GPIO, &usart_gpio);

	usart_gpio.GPIO_Pin = TX2_PIN;
	usart_gpio.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_Init(TX2_GPIO, &usart_gpio);

	/*
	 * USART configuration
	 */
	USART_Cmd(USART1, ENABLE);

	USART_InitTypeDef usart_conf;

	// usart_conf.USART_BaudRate=9600; HC-05
	usart_conf.USART_BaudRate = 19200; // BTM 222
	usart_conf.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	usart_conf.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	usart_conf.USART_Parity=USART_Parity_No;
	usart_conf.USART_StopBits=USART_StopBits_1;
	usart_conf.USART_WordLength=USART_WordLength_8b;

	USART_Init(USART1, &usart_conf);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	NVIC_EnableIRQ(USART1_IRQn);

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

		/*
		 * Proceed commands
		 */

		uint8_t data = USARTx->DR;
		if (data == 0xFF) // start command
		{
			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until next data
			data = USARTx->DR;

			switch(data)
			{
			case 0x00: //who am I?
				while ((USARTx->SR & USART_FLAG_RXNE) == RESET) {} //wait until line feed
				data = USARTx->DR;
				if (data == 0x0A) //line feed, everything ok.
				{
					/*
					 * Send my name
					 *
					 * The Reaper
					 *
					 */

					uint8_t name[10] = {'T', 'h', 'e', ' ', 'R', 'e', 'a', 'p', 'e', 'r'};
					int i = 0;
					for (i = 0; i < 10; i++)
					{
						while ((USARTx->SR & USART_FLAG_TXE) == RESET) {}
						USARTx->DR = name[i];
					}

					sendLineFeed(USARTx);
				}
				break;
			case 0x10:
			case 0x11: // Motor PWM
				while ((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
				data = USARTx->DR;

				if (data == 0x20) // set motor PWM
				{
					while((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
					data = USARTx->DR;

					//wait until line feed
					while((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
					if (USARTx->DR == 0x0A)
					{
						// if the oldest bit is 1 set direction to 1
						if (data & (0b1 << 7))
						{
							MOTOR1_DIR2_GPIO->ODR |= MOTOR1_DIR2_PIN;
							MOTOR1_DIR1_GPIO->ODR &= ~(MOTOR1_DIR1_PIN);
						}
						else
						{
							MOTOR1_DIR2_GPIO->ODR &= ~(MOTOR1_DIR2_PIN);
							MOTOR1_DIR1_GPIO->ODR |= MOTOR1_DIR1_PIN;
						}
						// first bit as direction
						data &= ~(0b1 << 7);
						TIM2->CCR1 = data;
					}
				}
				break;
			case 0x12: // Turn servo
				while ((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
				data = USARTx->DR;

				if (data == 0x21) // set servo PWM
				{
					while((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
					data = USARTx->DR;
					//wait until line feed
					while((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
					if (USARTx->DR == 0x0A)
						TIM3->CCR2 = (data + SERVO_COMPENSATION) + 255; // + 255 because 0 means 1 ms not 0
				}
				break;
			default:
				break;
			}
			//Enable receive interrupt
			USARTx->CR1 |= USART_CR1_RXNEIE;
		}
		else if (data == 0xAA) //Send back data
		{
			while((USARTx->SR & USART_FLAG_RXNE) == RESET) {}
			if (USARTx->DR == 0x0A)
			{
				USARTx->DR = 0xFF;
				USARTx->CR1 |= USART_CR1_TXEIE; // enable transmit interrupt
				/*
				 * Send data
				 * 1 byte start byte: 0xFF
				 * 1 byte battery level - 0 - 0%, 255 - 100%
				 * 1 byte servo current - 0 - 0, 255 - 3 A ?
				 * 1 byte motor current - 0 - 0, 255 - 15 A
				 * 1 byte accelerometer x - 127 - 0
				 * 1 byte accelerometer y - 127 - 0
				 * 1 byte line feed
				 */
				int8_t buffor[2];

				readI2C(I2C2, ACC_I2C, 0x04, 2, buffor); // Receive data from accelerometer
				globalData.acc_x = buffor[0];
				globalData.acc_y = buffor[1];
			}
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
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = globalData.acc_x;
		while((USARTx->SR & USART_SR_TXE) == RESET);
		USARTx->DR = globalData.acc_y;
		while((USARTx->SR & USART_SR_TXE) == RESET);
		sendLineFeed(USARTx);

		//Enable receive interrupt
		USARTx->CR1 |= USART_CR1_RXNEIE;
	}
}

void USART1_IRQHandler(void)
{
	USARTInterrupt(USART1);
}

void USART2_IRQHandler(void)
{
	USARTInterrupt(USART2);
}
