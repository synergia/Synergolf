#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdio.h>
#include <stdint.h>
#include "PinDefines.h"
#include "system_stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "data.h"

#define SPEED_DC_RANGE 1023
#define SPEED_DC_MAX 100
#define SPEED_DC_MIN 800
#define SPEED_STEPPER_MIN 332864
#define SERVO_COMPENSATION -30
#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define MOTORstepper 4
#define CW 1
#define CCW 2
#define STOP 3

void initializePWMTimer();
void initializeDirectionOutput();
void safeStop();
void setDCMotor(uint8_t MOTORx,uint16_t Speed, uint8_t direction);
void setStepperPosition(int Speed, int Steps, int Direction);

#endif
