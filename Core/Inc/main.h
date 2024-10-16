/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOC
#define SCL_Pin GPIO_PIN_15
#define SCL_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_2
#define BUZZER_GPIO_Port GPIOB
#define TRIG_Pin GPIO_PIN_10
#define TRIG_GPIO_Port GPIOB
#define ECHO_Pin GPIO_PIN_11
#define ECHO_GPIO_Port GPIOB
#define KEYboard_1_Pin GPIO_PIN_12
#define KEYboard_1_GPIO_Port GPIOB
#define KEYboard_1_EXTI_IRQn EXTI15_10_IRQn
#define KEYboard_2_Pin GPIO_PIN_13
#define KEYboard_2_GPIO_Port GPIOB
#define KEYboard_2_EXTI_IRQn EXTI15_10_IRQn
#define KEY_3_Pin GPIO_PIN_14
#define KEY_3_GPIO_Port GPIOB
#define KEY_3_EXTI_IRQn EXTI15_10_IRQn
#define KEY_2_Pin GPIO_PIN_15
#define KEY_2_GPIO_Port GPIOB
#define KEY_2_EXTI_IRQn EXTI15_10_IRQn
#define KEYboard_3_Pin GPIO_PIN_8
#define KEYboard_3_GPIO_Port GPIOA
#define KEYboard_3_EXTI_IRQn EXTI9_5_IRQn
#define KEY_1_Pin GPIO_PIN_10
#define KEY_1_GPIO_Port GPIOA
#define KEY_1_EXTI_IRQn EXTI15_10_IRQn
#define KEYboard_4_Pin GPIO_PIN_11
#define KEYboard_4_GPIO_Port GPIOA
#define KEYboard_4_EXTI_IRQn EXTI15_10_IRQn
#define MAX7219_DIN_Pin GPIO_PIN_15
#define MAX7219_DIN_GPIO_Port GPIOA
#define KEYboard_5_Pin GPIO_PIN_3
#define KEYboard_5_GPIO_Port GPIOB
#define KEYboard_5_EXTI_IRQn EXTI3_IRQn
#define CNT__Pin GPIO_PIN_4
#define CNT__GPIO_Port GPIOB
#define CNT__EXTI_IRQn EXTI4_IRQn
#define CNT_B5_Pin GPIO_PIN_5
#define CNT_B5_GPIO_Port GPIOB
#define CNT_B5_EXTI_IRQn EXTI9_5_IRQn
#define KEYboard_6_Pin GPIO_PIN_6
#define KEYboard_6_GPIO_Port GPIOB
#define KEYboard_6_EXTI_IRQn EXTI9_5_IRQn
#define MAX7219_CS_Pin GPIO_PIN_7
#define MAX7219_CS_GPIO_Port GPIOB
#define MAX7219_CLK_Pin GPIO_PIN_8
#define MAX7219_CLK_GPIO_Port GPIOB
#define KEYboard_7_Pin GPIO_PIN_9
#define KEYboard_7_GPIO_Port GPIOB
#define KEYboard_7_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
