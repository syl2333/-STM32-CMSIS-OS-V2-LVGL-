#ifndef __HEART_BEAT_OXYGEN_H__
#define __HEART_BEAT_OXYGEN_H__

#include "usart.h"
#include "stdint.h"
#pragma pack(push,1)
typedef struct
{
	int8_t acdata[64];
	uint8_t heartrate;
	uint8_t spo2;
	uint8_t bk;
	uint8_t rsv[8];
}RT_PACK;
#pragma pack(pop)

void start_data_cap();
void  stop_data_cap();
int heart_beat_test();

#endif // !__HEART_BEAT_OXYGEN_H__
