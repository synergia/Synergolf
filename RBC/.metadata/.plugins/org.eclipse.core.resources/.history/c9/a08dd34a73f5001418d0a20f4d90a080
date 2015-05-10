#include "LED.h"

void initializeLEDGPIO()
{
	GPIO_InitTypeDef led;

	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_2MHz; // to save power

	// GPIOA
	led.GPIO_Pin = LED6_PIN | LED7_PIN | LED8_PIN;
	GPIO_Init(GPIOA, &led);

	// GPIOB
	led.GPIO_Pin = LED4_PIN | LED5_PIN;
	GPIO_Init(GPIOB, &led);

	// GPIOC
	led.GPIO_Pin = LED1_PIN | LED2_PIN | LED3_PIN | LED9_PIN | LED10_PIN;
	GPIO_Init(GPIOC, &led);

	// Turn on all for about 1 sec (72 000 000 -> 72 MHz )
	GPIO_SetBits(GPIOA, LED6_PIN | LED7_PIN | LED8_PIN);
	GPIO_SetBits(GPIOB, LED4_PIN | LED5_PIN);
	GPIO_SetBits(GPIOC, LED1_PIN | LED2_PIN | LED3_PIN | LED9_PIN | LED10_PIN);

	uint32_t i = 0;
	for (i = 0; i < 1000000; i++)
	{
	}

	GPIO_ResetBits(GPIOA, LED6_PIN | LED7_PIN | LED8_PIN);
	GPIO_ResetBits(GPIOB, LED4_PIN | LED5_PIN);
	GPIO_ResetBits(GPIOC, LED1_PIN | LED2_PIN | LED3_PIN | LED9_PIN | LED10_PIN);
}
