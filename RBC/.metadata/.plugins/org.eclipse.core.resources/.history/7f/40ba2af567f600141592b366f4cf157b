#include "APBClocks.h"

void initializeAPB()
{
	/*
	 * PWM1, PWM2, TX2, RX2, IPOM3, IPOM4, ADC1, ADC2, LED8, RX, TX, LED7, LED6, DIR3
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*
	 * PWM3, PWM4, EN2, DIR1, EN1, LED4, LED5, SCL_UC, SDA_UC, SPI_SS, SPI_SCK, SPI_MISO, SPI_MOSI
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	/*
	 * BAT, IPOM1, IPOM2, ADC3, ADC4, PWM6, PWM5, LED10, LED9, EN3, DIR4, EN4, LED3, LED1, LED2
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/*
	 * DIR2
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	/*
	 * USART
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/*
	 * TIM2 - Motor PWM
	 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/*
	 * TIM 3 - Turn Servo PWM
	 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/*
	 * ADC
	 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	/*
	 * I2C2
	 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
}
