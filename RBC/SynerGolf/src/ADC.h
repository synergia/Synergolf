#ifndef ADC_H_
#define ADC_H_

#include <stdio.h>
#include <stdint.h>
#include "PinDefines.h"
#include "system_stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "data.h"
#include "LED.h"

#define ADC_MIN_VALUE 216

void initializeADC();
void initializeBatteryTimer();
#endif
