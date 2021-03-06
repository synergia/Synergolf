#ifndef DATA_H_
#define DATA_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
	dPutterRequest_None,
	dPutterRequest_stop,
	dPutterRequest_left,
	dPutterRequest_right,
	dPutterRequest_putt,
} PutterRequest_T;

typedef enum
{
	dPutterState_None,
	dPutterState_stop,
	dPutterState_left,
	dPutterState_right,
	dPutterState_putt,
	dPutterState_putting1,
	dPutterState_putting2,
	dPutterState_putting3,
} PutterState_T;

typedef enum
{
	dPutterDir_Left  = 0,
	dPutterDir_Right = 1,
} PutterDir_T;

typedef struct
{
	uint8_t bStartByteReceived;
	uint8_t communication_safety; //in SysTick, if still 0, safeStop

	uint8_t  sample;
	uint32_t battery_level_sum;
	uint32_t battery_level; // average from 256 samples

	int16_t stepsCounter;

	PutterDir_T putterDir;
	PutterRequest_T putterRequest;
	PutterState_T putterState;
} Data;

volatile Data globalData;

#endif
