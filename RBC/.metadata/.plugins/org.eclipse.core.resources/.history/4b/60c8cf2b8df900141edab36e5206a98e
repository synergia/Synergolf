#include "NVIC.h"

void initializeNVIC()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitTypeDef nvic_usart;
	nvic_usart.NVIC_IRQChannel = USART1_IRQn | USART2_IRQn;
	nvic_usart.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_usart.NVIC_IRQChannelSubPriority = 1;
	nvic_usart.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_usart);

	NVIC_InitTypeDef nvic_adc;
	nvic_adc.NVIC_IRQChannel = ADC1_2_IRQn;
	nvic_adc.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_adc.NVIC_IRQChannelSubPriority = 2;
	nvic_adc.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_adc);

}
