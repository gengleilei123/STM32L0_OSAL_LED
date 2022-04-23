/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
//#include "task_event.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED3(n)						(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET))
#define LED3_TogglePin		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_6)	//LED3_R电平翻转
#define LED4(n)						(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET))
#define LED4_TogglePin		HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_5)	//LED4_R电平翻转
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
