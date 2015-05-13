#include "motor.h"

void initializePWMTimer()
{
	GPIO_InitTypeDef pwmgpio;
	pwmgpio.GPIO_Mode = GPIO_Mode_AF_PP;
	pwmgpio.GPIO_Speed = GPIO_Speed_50MHz;

	pwmgpio.GPIO_Pin = MOTOR1_PWM1_PIN;
	GPIO_Init(MOTOR1_PWM1_GPIO, &pwmgpio);

	pwmgpio.GPIO_Pin = MOTOR1_PWM2_PIN;
	GPIO_Init(MOTOR1_PWM2_GPIO, &pwmgpio);

	pwmgpio.GPIO_Pin = MOTOR2_PWM4_PIN;
	GPIO_Init(MOTOR2_PWM4_GPIO, &pwmgpio);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);



    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 19; //PWM 3.6kHz
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 999;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timerInitStructure);//PWM3
    TIM_TimeBaseInit(TIM4, &timerInitStructure);//PWM4
    TIM_Cmd(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 100;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM3, &outputChannelInit);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM4, &outputChannelInit);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

void initializeDirectionOutput()
{
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE); // Disable NJTRST, PB4 is Alternate Function
	GPIO_InitTypeDef dir;
	dir.GPIO_Mode = GPIO_Mode_Out_PP;
	dir.GPIO_Speed = GPIO_Speed_2MHz;

	dir.GPIO_Pin = MOTOR1_IN1A_PIN;
	GPIO_Init(MOTOR1_IN1A_GPIO, &dir);

	dir.GPIO_Pin = MOTOR1_IN1B_PIN;
	GPIO_Init(MOTOR1_IN1B_GPIO, &dir);

	dir.GPIO_Pin = MOTOR1_IN2A_PIN;
	GPIO_Init(MOTOR1_IN2A_GPIO, &dir);

	dir.GPIO_Pin = MOTOR1_IN2B_PIN;
	GPIO_Init(MOTOR1_IN2B_GPIO, &dir);

	dir.GPIO_Pin = MOTOR2_IN2A_PIN;
	GPIO_Init(MOTOR2_IN2A_GPIO, &dir);

	dir.GPIO_Pin = MOTOR2_IN2B_PIN;
	GPIO_Init(MOTOR2_IN2B_GPIO, &dir);

	//stepper
	dir.GPIO_Pin =  MOTOR_STEPPER_CLK_PIN;
	GPIO_Init( MOTOR_STEPPER_CLK_GPIO, &dir);

	dir.GPIO_Pin =  MOTOR_STEPPER_CW_PIN;
	GPIO_Init( MOTOR_STEPPER_CW_GPIO, &dir);

	dir.GPIO_Pin =  MOTOR_STEPPER_EN_PIN;
	GPIO_Init( MOTOR_STEPPER_EN_GPIO, &dir);
}

void setDCMotor(uint8_t MOTORx,uint16_t Speed, uint8_t direction){ //dir: CW, CCW, STOP
	Speed = (SPEED_DC_RANGE - Speed);
	if(Speed<SPEED_DC_MAX) Speed = SPEED_DC_MAX;
	else if(Speed>SPEED_DC_MIN) Speed = SPEED_DC_RANGE;
	//speed od 100 do 1023;
	if(MOTORx==MOTOR1){
		if(direction==CW){
			GPIO_SetBits(MOTOR1_IN1A_GPIO, MOTOR1_IN1A_PIN);
			GPIO_ResetBits(MOTOR1_IN1B_GPIO, MOTOR1_IN1B_PIN);
		}
		else if(direction==CCW){
			GPIO_ResetBits(MOTOR1_IN1A_GPIO, MOTOR1_IN1A_PIN);
			GPIO_SetBits(MOTOR1_IN1B_GPIO, MOTOR1_IN1B_PIN);
		}
		else /*if(direction==STOP)*/{
			GPIO_ResetBits(MOTOR1_IN1A_GPIO, MOTOR1_IN1A_PIN);
			GPIO_ResetBits(MOTOR1_IN1B_GPIO, MOTOR1_IN1B_PIN);
		}

		TIM3->CCR1 = Speed; //M1 PWM (out 0f 1000)
	}
	else if(MOTORx==MOTOR2){
		if(direction==CW){
			GPIO_SetBits(MOTOR1_IN2A_GPIO, MOTOR1_IN2A_PIN);
			GPIO_ResetBits(MOTOR1_IN2B_GPIO, MOTOR1_IN2B_PIN);
		}
		else if(direction==CCW){
			GPIO_ResetBits(MOTOR1_IN2A_GPIO, MOTOR1_IN2A_PIN);
			GPIO_SetBits(MOTOR1_IN2B_GPIO, MOTOR1_IN2B_PIN);
		}
		else /*if(direction==STOP)*/{
			GPIO_ResetBits(MOTOR1_IN2A_GPIO, MOTOR1_IN2A_PIN);
			GPIO_ResetBits(MOTOR1_IN2B_GPIO, MOTOR1_IN2B_PIN);
		}
		TIM3->CCR4 = Speed; //M2
	}
	else if(MOTORx==MOTOR3){
		if(direction==CW){
			GPIO_SetBits(MOTOR2_IN2A_GPIO, MOTOR2_IN2A_PIN);
			GPIO_ResetBits(MOTOR2_IN2B_GPIO, MOTOR2_IN2B_PIN);
		}
		else if(direction==CCW){
			GPIO_ResetBits(MOTOR2_IN2A_GPIO, MOTOR2_IN2A_PIN);
			GPIO_SetBits(MOTOR2_IN2B_GPIO, MOTOR2_IN2B_PIN);
		}
		else /*if(direction==STOP)*/{
			GPIO_ResetBits(MOTOR2_IN2A_GPIO, MOTOR2_IN2A_PIN);
			GPIO_ResetBits(MOTOR2_IN2B_GPIO, MOTOR2_IN2B_PIN);
		}
		TIM4->CCR4 = Speed; //M3
	}
}

void setStepperPosition(int Speed, int Steps, int Direction){
	if(Direction==CW){
		GPIO_ResetBits( MOTOR_STEPPER_CW_GPIO, MOTOR_STEPPER_CW_PIN);
		GPIO_ResetBits( MOTOR_STEPPER_EN_GPIO, MOTOR_STEPPER_EN_PIN);
	}
	else if(Direction==CCW){
		GPIO_ResetBits( MOTOR_STEPPER_EN_GPIO, MOTOR_STEPPER_EN_PIN);
		GPIO_SetBits( MOTOR_STEPPER_CW_GPIO, MOTOR_STEPPER_CW_PIN);
	}
	else /*if(direction==STOP)*/{
		GPIO_SetBits( MOTOR_STEPPER_EN_GPIO, MOTOR_STEPPER_EN_PIN);
	}
	SysTick_Config(SPEED_STEPPER_MIN-(Speed<<10));
	globalData.steps = Steps;
}
void safeStop()
{
	//TIM2->CCR1 = 0; // stop motor
	//TIM3->CCR2 = 127+255;
}
