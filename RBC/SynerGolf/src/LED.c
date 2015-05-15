#include "LED.h"


void initializeLEDGPIO()
{
	GPIO_InitTypeDef led;

	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_2MHz; // to save power

	// GPIOA
	led.GPIO_Pin = 	LED3_PIN |
					LED_MOTOR1_CW_PIN | LED_MOTOR1_CCW_PIN |
					LED_MOTOR2_CW_PIN | LED_MOTOR2_CCW_PIN |
					LED_MOTOR3_CW_PIN | LED_MOTOR3_CCW_PIN |
					LED_ADC_RED_PIN  | LED_ADC_GREEN_PIN;
	GPIO_Init(GPIOA, &led);

	// GPIOB
	led.GPIO_Pin = LED2_PIN | LED4_PIN;
	GPIO_Init(GPIOB, &led);

	// GPIOC
	led.GPIO_Pin = LED1_PIN;
	GPIO_Init(GPIOC, &led);

	LEDs_SHOW_OFF();
	// Turn on all for about 1 sec (72 000 000 -> 72 MHz )
	GPIO_SetBits(GPIOA, LED3_PIN);
	GPIO_SetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_SetBits(GPIOC, LED1_PIN);

	delay(1000);
	GPIO_ResetBits(GPIOA, LED3_PIN);
	GPIO_ResetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_ResetBits(GPIOC, LED1_PIN);
	delay(1000);

	GPIO_SetBits(GPIOA, LED3_PIN);
	GPIO_SetBits(GPIOB, LED2_PIN | LED4_PIN);
	GPIO_SetBits(GPIOC, LED1_PIN);
}

void LEDs_SHOW_OFF(){
	int Delay = 150;

	LED_MOTOR1_CW_ON;
	LED_MOTOR1_CCW_ON;
	LED_MOTOR2_CW_ON;
	LED_MOTOR2_CCW_ON;
	LED_MOTOR3_CW_ON;
	LED_MOTOR3_CCW_ON;
	delay(Delay);
	LED_off();
	delay(Delay);
	LED_MOTOR1_CW_ON;
	LED_MOTOR1_CCW_ON;
	LED_MOTOR2_CW_ON;
	LED_MOTOR2_CCW_ON;
	LED_MOTOR3_CW_ON;
	LED_MOTOR3_CCW_ON;
	delay(Delay);
	LED_off();
	delay(Delay);

	LED_MOTOR1_CW_ON;
	delay(Delay);
	LED_MOTOR1_CCW_ON;
	delay(Delay);
	LED_MOTOR2_CW_ON;
	delay(Delay);
	LED_MOTOR2_CCW_ON;
	delay(Delay);
	LED_MOTOR3_CW_ON;
	delay(Delay);
	LED_MOTOR3_CCW_ON;
	delay(Delay);
	LED_MOTOR1_CW_OFF;
	delay(Delay);
	LED_MOTOR1_CCW_OFF;
	delay(Delay);
	LED_MOTOR2_CW_OFF;
	delay(Delay);
	LED_MOTOR2_CCW_OFF;
	delay(Delay);
	LED_MOTOR3_CW_OFF;
	delay(Delay);
	LED_MOTOR3_CCW_OFF;
	delay(Delay);
	LED_MOTOR1_CW_ON;
	delay(Delay);
	LED_MOTOR1_CCW_ON;
	delay(Delay);
	LED_MOTOR2_CW_ON;
	delay(Delay);
	LED_MOTOR2_CCW_ON;
	delay(Delay);
	LED_MOTOR3_CW_ON;
	delay(Delay);
	LED_MOTOR3_CCW_ON;
	delay(Delay);
	LED_MOTOR1_CW_OFF;
	delay(Delay);
	LED_MOTOR1_CCW_OFF;
	delay(Delay);
	LED_MOTOR2_CW_OFF;
	delay(Delay);
	LED_MOTOR2_CCW_OFF;
	delay(Delay);
	LED_MOTOR3_CW_OFF;
	delay(Delay);
	LED_MOTOR3_CCW_OFF;
	delay(Delay);
}
void LED_off(){
	LED_MOTOR1_CW_OFF;
	LED_MOTOR1_CCW_OFF;
	LED_MOTOR2_CW_OFF;
	LED_MOTOR2_CCW_OFF;
	LED_MOTOR3_CW_OFF;
	LED_MOTOR3_CCW_OFF;
}
