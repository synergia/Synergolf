#include "SysTick.h"
#include "data.h"
#include "motor.h"
#include "I2C.h"

extern volatile Data globalData;

void initializeSysTick()
{
	/*
	 * Interrupt every 1s:
	 * 72 MHz / 8 = 9 -> count to 9000000
	 */
	SysTick_Config(100000ul);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void SysTick_Handler(void)
{
	if(globalData.steps>0){
		MOTOR_STEPPER_CLK_GPIO->ODR ^= MOTOR_STEPPER_CLK_PIN;
		globalData.steps--;
	}

	// check €connection
	if (globalData.communication_safety == 0)
		safeStop();
	globalData.communication_safety = 0;
}
