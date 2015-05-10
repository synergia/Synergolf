#include "I2C.h"

void initializeI2C()
{
	GPIO_InitTypeDef i2c_gpio;
	i2c_gpio.GPIO_Speed = GPIO_Speed_10MHz;
	i2c_gpio.GPIO_Pin = I2C2_SCL_PIN | I2C2_SDA_PIN;
	i2c_gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(I2C2_GPIO, &i2c_gpio);

	I2C_InitTypeDef i2c;
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_DutyCycle = I2C_DutyCycle_2;
	i2c.I2C_OwnAddress1 = 0x55;
	i2c.I2C_Ack = I2C_Ack_Enable;
	i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	i2c.I2C_ClockSpeed = 20000;

	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2, &i2c);
	I2C_AcknowledgeConfig(I2C2, ENABLE);

	I2C2->CCR = 0x01F4; // datasheet according to resistors
}

void readI2C(I2C_TypeDef *I2Cx, uint8_t address, uint8_t first_reg, uint8_t length, int8_t *buffor)
{
	while(I2Cx->SR2 & I2C_SR2_BUSY)
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->CR1 |= I2C_CR1_START; // Send START
	while(!(I2Cx->SR1 & I2C_SR1_SB))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->DR = address << 1; //ACC Address + RW Bit
	while(!(I2Cx->SR1 & I2C_SR1_ADDR))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->SR2;
	while(!(I2Cx->SR1 & I2C_SR1_TXE))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->DR = first_reg; // register addres
	while (!(I2Cx->SR1 & I2C_SR1_BTF))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->CR1 |= I2C_CR1_START; // Send START
	while (!(I2Cx->SR1 & I2C_SR1_SB))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->DR = (address << 1) | 0x01; // Add R/W one
	while (!(I2Cx->SR1 & I2C_SR1_ADDR))
	{
		if (checkI2CErrors(I2Cx))
			return;
	}

	I2Cx->SR2;

	I2Cx->CR1 |= I2C_CR1_ACK;

	for(; length > 0; length--)
	{
		if (length == 1)
			I2Cx->CR1 &= ~(I2C_CR1_ACK);

		while (!(I2Cx->SR1 & I2C_SR1_RXNE))
		{
			if (checkI2CErrors(I2Cx))
				return;
		}
		*(buffor) = I2Cx->DR;
		buffor++;
	}
	I2Cx->CR1 |= I2C_CR1_STOP;
}

int checkI2CErrors(I2C_TypeDef *I2Cx)
{
	if((I2Cx->SR1 & I2C_SR1_TIMEOUT) | (I2Cx->SR1 & I2C_SR1_PECERR) | (I2Cx->SR1 & I2C_SR1_AF) | (I2Cx->SR1 & I2C_SR1_ARLO) |
				(I2Cx->SR1 & I2C_SR1_BERR))
	{
		// reset errors
		I2Cx->SR1 &= ~(I2C_SR1_ARLO);
		I2Cx->SR1 &= ~(I2C_SR1_AF);
		I2Cx->SR1 &= ~(I2C_SR1_TIMEOUT);
		I2Cx->SR1 &= ~(I2C_SR1_PECERR);
		I2Cx->SR1 &= ~(I2C_SR1_BERR);

		I2C2->CR1 |= I2C_CR1_STOP;
		return 1;
	}
	return 0;
}
