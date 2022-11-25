/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_Backlight_Pin GPIO_PIN_9
#define LCD_Backlight_GPIO_Port GPIOF
#define MPU_6050_INT_Pin GPIO_PIN_10
#define MPU_6050_INT_GPIO_Port GPIOF
#define MPU_6050_INT_EXTI_IRQn EXTI15_10_IRQn
#define LCD_RST_Pin GPIO_PIN_11
#define LCD_RST_GPIO_Port GPIOF
#define GTP_INT_Pin GPIO_PIN_8
#define GTP_INT_GPIO_Port GPIOG
#define GTP_INT_EXTI_IRQn EXTI9_5_IRQn
#define GTP_SDA_Pin GPIO_PIN_3
#define GTP_SDA_GPIO_Port GPIOD
#define GTP_RST_Pin_Pin GPIO_PIN_6
#define GTP_RST_Pin_GPIO_Port GPIOD
#define GTP_SCL_Pin GPIO_PIN_7
#define GTP_SCL_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
