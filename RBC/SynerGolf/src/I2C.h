#ifndef I2C_H_
#define I2C_H_

#define ACC_I2C 0x0A //accelerometer i2c address

#include <stdio.h>
#include <stdint.h>
#include "system_stm32f10x.h"
#include "stm32f10x.h"

#include "PinDefines.h"
#include "data.h"

extern volatile Data data;

void initializeI2C();
void readI2C(I2C_TypeDef *I2Cx, uint8_t address, uint8_t first_reg, uint8_t length, int8_t *buffor);
int checkI2CErrors(I2C_TypeDef *I2Cx);

#endif
