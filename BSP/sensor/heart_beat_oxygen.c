#include "heart_beat_oxygen.h"

uint8_t command_start = 0x8A;
uint8_t command_stop = 0x88;
uint8_t head_check = 0xFF;

void start_data_cap()
{
	HAL_UART_Transmit(&huart1,&command_start,1,1000);
}
void stop_data_cap()
{
	HAL_UART_Transmit(&huart1,&command_stop,1,1000);
}
int heart_beat_test()
{
	RT_PACK data_pack;
	uint8_t temp = 0;
	start_data_cap();
	while(1)
	{
		HAL_UART_Receive(&huart1,&temp,sizeof(uint8_t),100);
		if(temp == 0xFF)
		{
			return 1;
		}
	}
}