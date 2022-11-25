/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
#include "lvgl_ui.h"
#include "gt5xx.h"

#include "usart.h"
#include "heart_beat_oxygen.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osEventFlagsAttr_t GT_Touch_ISR_Event_Attr = {
	.name = "GT_Touch_ISR_Event",
	.attr_bits = 0,
	.cb_mem	 = NULL,
	.cb_size = 0,
};
osEventFlagsId_t GT_Touch_ID;


static unsigned long cnt = 0;
RT_PACK data;
extern lv_chart_series_t* ser1;
extern lv_obj_t* heart_chart;
/* USER CODE END Variables */
/* Definitions for GT_Touch_ISR_Cb */
osThreadId_t GT_Touch_ISR_CbHandle;
const osThreadAttr_t GT_Touch_ISR_Cb_attributes = {
  .name = "GT_Touch_ISR_Cb",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for lv_task_handler */
osThreadId_t lv_task_handlerHandle;
const osThreadAttr_t lv_task_handler_attributes = {
  .name = "lv_task_handler",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MPU_Data_Get_Ta */
osThreadId_t MPU_Data_Get_TaHandle;
const osThreadAttr_t MPU_Data_Get_Ta_attributes = {
  .name = "MPU_Data_Get_Ta",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Heart_Beat_Task */
osThreadId_t Heart_Beat_TaskHandle;
const osThreadAttr_t Heart_Beat_Task_attributes = {
  .name = "Heart_Beat_Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for MPU_INT_Event */
osEventFlagsId_t MPU_INT_EventHandle;
const osEventFlagsAttr_t MPU_INT_Event_attributes = {
  .name = "MPU_INT_Event"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void GT_Touch_ISR_Entry(void *argument);
void lv_task_entry(void *argument);
void MPU_task_entry(void *argument);
void Heart_Beat_Entry(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
	lv_tick_inc(1);
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */

  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of GT_Touch_ISR_Cb */
  GT_Touch_ISR_CbHandle = osThreadNew(GT_Touch_ISR_Entry, NULL, &GT_Touch_ISR_Cb_attributes);

  /* creation of lv_task_handler */
  lv_task_handlerHandle = osThreadNew(lv_task_entry, NULL, &lv_task_handler_attributes);

  /* creation of MPU_Data_Get_Ta */
  MPU_Data_Get_TaHandle = osThreadNew(MPU_task_entry, NULL, &MPU_Data_Get_Ta_attributes);

  /* creation of Heart_Beat_Task */
  Heart_Beat_TaskHandle = osThreadNew(Heart_Beat_Entry, NULL, &Heart_Beat_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of MPU_INT_Event */
  MPU_INT_EventHandle = osEventFlagsNew(&MPU_INT_Event_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
 
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_GT_Touch_ISR_Entry */
/**
  * @brief  Function implementing the GT_Touch_ISR_Cb thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_GT_Touch_ISR_Entry */
void GT_Touch_ISR_Entry(void *argument)
{
  /* USER CODE BEGIN GT_Touch_ISR_Entry */
  /* Infinite loop */
  for(;;)
  {
	osDelay(50);	
  }
  /* USER CODE END GT_Touch_ISR_Entry */
}

/* USER CODE BEGIN Header_lv_task_entry */
/**
* @brief Function implementing the lv_tak_handler thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lv_task_entry */
void lv_task_entry(void *argument)
{
  /* USER CODE BEGIN lv_task_entry */
  /* Infinite loop */
  for(;;)
  {
	
	lv_task_handler();
	osDelay(5);
		
  }
  /* USER CODE END lv_task_entry */
}

/* USER CODE BEGIN Header_MPU_task_entry */
/**
* @brief Function implementing the MPU_Data_Get_Ta thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MPU_task_entry */
void MPU_task_entry(void *argument)
{
  /* USER CODE BEGIN MPU_task_entry */
  /* Infinite loop */
  for(;;)
  {
	
	pedometer_cnt_fresh();
	osEventFlagsClear(MPU_INT_EventHandle,1);
  osDelay(100);
  }
  /* USER CODE END MPU_task_entry */
}

/* USER CODE BEGIN Header_Heart_Beat_Entry */
/**
* @brief Function implementing the Heart_Beat_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Heart_Beat_Entry */
void Heart_Beat_Entry(void *argument)
{
  /* USER CODE BEGIN Heart_Beat_Entry */
  /* Infinite loop */
	
  for(;;)
  {
	uint8_t temp = 0;
	HAL_UART_Receive(&huart1,&temp,1,100);
	if(temp == 0xFF)
	{
		if(HAL_UART_Receive(&huart1,(uint8_t*)&data,sizeof(RT_PACK),500) == HAL_OK)
		{
			heart_rate_fresh(data.heartrate);
			oxygen_rate_fresh(data.spo2);
		}
	}
	
    osDelay(1);
  }
  /* USER CODE END Heart_Beat_Entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
