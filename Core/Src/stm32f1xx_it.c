/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Passive_Buzzer.h"
#include "math.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern int cnt;
extern unsigned char msHcCount;

extern int8_t Encoder_Count;

extern uint8_t voice;               // �ⲿ��ɫ����
extern uint8_t sharp;
extern uint16_t scale[];                 // ��������
extern uint16_t transpose[];             // ת������
extern uint8_t voiceDuties[];            // ��ɫռ�ձ�����
extern uint8_t sft, tsp, oct;            // ���Ʊ���
extern uint8_t mode;                     // ģʽѡ�����
extern uint8_t isPlaying;                // ���ಥ�ű���
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */
    // ����Ƿ�Ϊ EXTI3 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) {
        // ����ټ�״̬��PB3��
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET) {  // ��������ټ�
            if (voice == 6) {  // �����ɫ����Ϊ����
                Passive_Buzzer_Drum(5);
                HAL_Delay(70);  // ʹ�� HAL_Delay �滻 Delay_ms
            } else {  // �����ɫ����Ϊ������ɫ
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[4 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        // ����ⲿ�жϱ�־
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
    }
  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEYboard_5_Pin);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
    {

        // 切换LED状�??
        cnt++;
        if (cnt > 99) // ����������ֵ
        {
            cnt = 99; // ����Ϊ100����ֹ���
        }
        // 清除中断标志
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
    }

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(CNT__Pin);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
    {

        // 切换LED状�??
        cnt--;
        if (cnt < 0) // ����������ֵ
        {
            cnt = 0; // ����Ϊ100����ֹ���
        }
        // 清除中断标志
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
    }

    // ����Ƿ�Ϊ EXTI8 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {  // ��� PA8 ״̬
            if (voice == 6) {
                Passive_Buzzer_Drum(3);
                HAL_Delay(70);  // ʹ�� HAL_Delay ��� Delay_ms
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[2 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI6 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET) {  // ��� PB6 ״̬
            if (voice == 6) {
                if (sharp == 1) {
                    Passive_Buzzer_Drum(8);
                } else {
                    Passive_Buzzer_Drum(6);
                }
                HAL_Delay(70);
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[5 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI9 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET) {  // ��� PB9 ״̬
            if (voice == 6) {
                if (sharp == 1) {
                    Passive_Buzzer_Drum(9);
                } else {
                    Passive_Buzzer_Drum(7);
                }
                HAL_Delay(70);
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[6 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);  // ����жϱ�־
    }
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(CNT_B5_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_6_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_3_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_7_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt.
  */
void TIM1_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_IRQn 0 */
    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) != RESET)  // ��鶨ʱ���жϷ���
    {
        if (__HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_UPDATE) != RESET)
        {
            msHcCount++;

            __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);  // ����жϱ�־
        }
    }
  /* USER CODE END TIM1_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_IRQn 1 */
//
  /* USER CODE END TIM1_UP_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */


    // ����Ƿ�Ϊ EXTI11 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET) { // ��� PA11 ״̬
            if (voice == 6) {
                Passive_Buzzer_Drum(4);
                HAL_Delay(70);  // ʹ�� HAL_Delay ��� Delay_ms
                Passive_Buzzer_OFF(2);
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[3 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI12 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) { // ��� PB12 ״̬
            if (voice == 6) {
                Passive_Buzzer_Drum(1);
                HAL_Delay(70);
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[0 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI13 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) {
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) { // ��� PB13 ״̬
            if (voice == 6) {
                Passive_Buzzer_Drum(2);
                HAL_Delay(70);
            } else {
                Passive_Buzzer_Reset(1);
                uint16_t freq = scale[1 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
            }
        } else {  // ����ɿ��ټ�
            Passive_Buzzer_OFF(1);
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI10 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) {
        if (mode == 1 || isPlaying == 1) {  // ������ɫģʽ����ಥ��ʱ
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET) { // ��� PA10 ״̬
                oct = 0;  // ���˶���Ϊ 0
            } else {
                oct = 1;  // ���˶���Ϊ 1
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI15 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) {
        if (mode == 1 || isPlaying == 1) {  // ������ɫģʽ����ಥ��ʱ
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET) { // ��� PB15 ״̬
                oct = 2;  // ���˶���Ϊ 2
            } else {
                oct = 1;  // ���˶���Ϊ 1
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);  // ����жϱ�־
    }

    // ����Ƿ�Ϊ EXTI14 ���ж�
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) {
        if (mode == 1 || isPlaying == 1) {  // ������ɫģʽ����ಥ��ʱ
            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) { // ��� PB14 ״̬
                sharp = 1;  // ���� sharp Ϊ 1
            } else {
                sharp = 0;  // ���� sharp Ϊ 0
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);  // ����жϱ�־
    }

//    // ����Ƿ�ΪEXTI10���ж�
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET) { // ���PB11״̬
//            Encoder_Count = 1;  // ��������
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);  // ����жϱ�־
//    }
//
//    // ����Ƿ�ΪEXTI11���ж�
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET) { // ���PB10״̬
//            Encoder_Count = -1; // ��������
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);  // ����жϱ�־
//    }
  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_1_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_4_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_1_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEYboard_2_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_3_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_2_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
//    // �?查是否为KEY引脚的中�?
//
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
