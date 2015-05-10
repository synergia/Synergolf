#ifndef LED_H_
#define LED_H_

#include <stdio.h>
#include <stdint.h>
#include "PinDefines.h"
#include "system_stm32f10x.h"
#include "stm32f10x_gpio.h"


#define LED1_OFF GPIO_SetBits(LED1_GPIO, LED1_PIN)
#define LED2_OFF GPIO_SetBits(LED2_GPIO, LED2_PIN)
#define LED3_OFF GPIO_SetBits(LED3_GPIO, LED3_PIN)
#define LED4_OFF GPIO_SetBits(LED4_GPIO, LED4_PIN)

#define LED1_ON GPIO_ResetBits(LED1_GPIO, LED1_PIN)
#define LED2_ON GPIO_ResetBits(LED2_GPIO, LED2_PIN)
#define LED3_ON GPIO_ResetBits(LED3_GPIO, LED3_PIN)
#define LED4_ON GPIO_ResetBits(LED4_GPIO, LED4_PIN)

void initializeLEDGPIO();
void LED_off();

#endif