#include "LED.h"


void initializeLEDGPIO()
{
	GPIO_InitTypeDef led;

	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_2MHz; // to save power

	// GPIOA
	led.GPIO_Pin = 	LED3_PIN |
					LED_MOTOR1_L_PIN | LED_MOTOR1_R_PIN |
					LED_MOTOR2_L_PIN | LED_MOTOR2_R_PIN |
					LED_MOTOR3_L_PIN | LED_MOTOR3_R_PIN |
					LED_ADC_RED_PIN  | LED_ADC_GREEN_PIN;
	GPIO_Init(GPIOA, &led);

	// GPIOB
	led.GPIO_Pin = LED2_PIN | LED4_PIN;
	GPIO_Init(GPIOB, &led);

	// GPIOC
	led.GPIO_Pin = LED1_PIN;
	GPIO_Init(GPIOC, &led);

	// Turn on all for about 1 sec (72 000 000 -> 72 MHz )
	GPIO_SetBits(GPIOA, LED3_PIN);
	GPIO_SetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_SetBits(GPIOC, LED1_PIN);

	uint32_t i = 0;
	for (i = 0; i < 4000000; i++){
	}
	GPIO_ResetBits(GPIOA, LED3_PIN/* | LED7_PIN | LED8_PIN*/);
	GPIO_ResetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_ResetBits(GPIOC, LED1_PIN /*| LED2_PIN | LED3_PIN | LED9_PIN | LED10_PIN*/);
	for (i = 0; i < 4000000; i++){
	}

	GPIO_SetBits(GPIOA, LED3_PIN/* | LED7_PIN | LED8_PIN*/);
	GPIO_SetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_SetBits(GPIOC, LED1_PIN /*| LED2_PIN | LED3_PIN | LED9_PIN | LED10_PIN*/);
}

void LED_off(){
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
}
