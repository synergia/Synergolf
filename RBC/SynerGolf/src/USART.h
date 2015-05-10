#ifndef USART_H_
#define USART_H_

#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "PinDefines.h"
#include "data.h"
#include "I2C.h"
#include "motor.h"

extern volatile Data data;

void initializeUSART();

void USARTInterrupt(USART_TypeDef *USARTx);
void sendLineFeed(USART_TypeDef *USARTx);
void USARTSend(USART_TypeDef *USARTx);

void initializeUSARTSendTimer();

#endif
