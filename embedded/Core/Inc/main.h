/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

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
extern SPI_HandleTypeDef hspi2;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BOILER_PUMP_Pin GPIO_PIN_4
#define BOILER_PUMP_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define MLT_CS_Pin GPIO_PIN_3
#define MLT_CS_GPIO_Port GPIOI
#define BUTTON_BLACK_Pin GPIO_PIN_2
#define BUTTON_BLACK_GPIO_Port GPIOI
#define BUTTON_BLACK_EXTI_IRQn EXTI2_IRQn
#define LCD_BL_CTRL_Pin GPIO_PIN_3
#define LCD_BL_CTRL_GPIO_Port GPIOK
#define LCD_DISP_Pin GPIO_PIN_12
#define LCD_DISP_GPIO_Port GPIOI
#define HLT_CS_Pin GPIO_PIN_0
#define HLT_CS_GPIO_Port GPIOI
#define BOIL_CS_Pin GPIO_PIN_8
#define BOIL_CS_GPIO_Port GPIOA
#define HLT_HEATER_Pin GPIO_PIN_7
#define HLT_HEATER_GPIO_Port GPIOC
#define HLT_PUMP_Pin GPIO_PIN_6
#define HLT_PUMP_GPIO_Port GPIOC
#define BOILER_HEATER_Pin GPIO_PIN_7
#define BOILER_HEATER_GPIO_Port GPIOG
#define MLT_PUMP_Pin GPIO_PIN_6
#define MLT_PUMP_GPIO_Port GPIOG
#define BUTTON_GREEN_Pin GPIO_PIN_0
#define BUTTON_GREEN_GPIO_Port GPIOA
#define BUTTON_GREEN_EXTI_IRQn EXTI0_IRQn
#define BUTTON_RED_Pin GPIO_PIN_6
#define BUTTON_RED_GPIO_Port GPIOH
#define BUTTON_RED_EXTI_IRQn EXTI9_5_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
