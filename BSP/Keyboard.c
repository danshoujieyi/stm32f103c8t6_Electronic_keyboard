#include "Passive_Buzzer.h"
#include "stm32f1xx_hal.h"
#include "PWM.h"
#include "math.h"

//extern uint8_t voice;               // 外部音色变量
//extern uint8_t sharp;
//extern uint16_t scale[];                 // 音阶数组
//extern uint16_t transpose[];             // 转音数组
//extern uint8_t voiceDuties[];            // 音色占空比数组
//extern uint8_t sft, tsp, oct;            // 控制变量
//extern uint8_t mode;                     // 模式选择变量
//extern uint8_t isPlaying;                // 伴奏播放变量

//void Keyboard_Init(void) {
//    // 使能 GPIOA、GPIOB 和 AFIO 时钟
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_AFIO_CLK_ENABLE();
//
//    // 配置 GPIOA 引脚为下拉输入
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.Pin = GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_10;
//    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;          // 设置为输入模式
//    GPIO_InitStructure.Pull = GPIO_PULLDOWN;            // 设置为下拉模式
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    // 设置速度为高速
//    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);          // 初始化 GPIOA
//
//    // 连接引脚到 EXTI (PA8, PA10, PA11)
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);               // 清除 EXTI 线路的中断标志
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);
//
//    // 配置 GPIOB 引脚为下拉输入
//    GPIO_InitStructure.Pin = GPIO_PIN_3 | GPIO_PIN_6 | // PB3，PB6，PB7，PB11，PB2，PB3，PB4
//                             GPIO_PIN_9 | GPIO_PIN_12 |
//                             GPIO_PIN_13 | GPIO_PIN_14 |
//                             GPIO_PIN_15; // 配置引脚
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);          // 初始化 GPIOB
//
//    // 连接引脚到 EXTI (PB3, PB6, PB9, PB12, PB13, PB14, PB15)
//    // 清除所有的中断标志
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);
//
//    // 配置 EXTI 中断
//    EXTI_ConfigTypeDef EXTI_InitStructure;
//    EXTI_InitStructure.Line = EXTI_LINE_8 | EXTI_LINE_10 |
//                              EXTI_LINE_11 | EXTI_LINE_3 |
//                              EXTI_LINE_6 | EXTI_LINE_9 |
//                              EXTI_LINE_12 | EXTI_LINE_13 |
//                              EXTI_LINE_14 | EXTI_LINE_15; // 设置所有需要的外部中断线路
//    EXTI_InitStructure.LineCmd = ENABLE;   // 启用外部中断
//    EXTI_InitStructure.Mode = EXTI_MODE_INTERRUPT; // 中断模式
//    EXTI_InitStructure.Trigger = EXTI_TRIGGER_RISING_FALLING; // 设置为上升下降沿触发
//    HAL_EXTI_Config(&EXTI_InitStructure);   // 应用配置
//
//    // 配置 NVIC 中断优先级
//    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);     // 配置 EXTI3 中断优先级
//    HAL_NVIC_EnableIRQ(EXTI3_IRQn);              // 使能 EXTI3 中断
//
//    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);    // 配置 EXTI9_5 中断优先级
//    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);             // 使能 EXTI9_5 中断
//
//    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);   // 配置 EXTI15_10 中断优先级
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);            // 使能 EXTI15_10 中断
//}

/////* 键盘弹奏中断函数 */
//void EXTI3_IRQHandler(void) {
//    // 检查是否为 EXTI3 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_3) != RESET) {
//        // 检查琴键状态（PB3）
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET) {  // 如果按下琴键
//            if (voice == 6) {  // 如果音色设置为鼓组
//                Passive_Buzzer_Drum(5);
//                HAL_Delay(70);  // 使用 HAL_Delay 替换 Delay_ms
//            } else {  // 如果音色设置为旋律音色
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[4 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        // 清除外部中断标志
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
//    }
//}
//
//void EXTI9_5_IRQHandler(void) {
//    // 检查是否为 EXTI8 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {  // 检查 PA8 状态
//            if (voice == 6) {
//                Passive_Buzzer_Drum(3);
//                HAL_Delay(70);  // 使用 HAL_Delay 替代 Delay_ms
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[2 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI6 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_SET) {  // 检查 PB6 状态
//            if (voice == 6) {
//                if (sharp == 1) {
//                    Passive_Buzzer_Drum(8);
//                } else {
//                    Passive_Buzzer_Drum(6);
//                }
//                HAL_Delay(70);
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[5 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI9 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_SET) {  // 检查 PB9 状态
//            if (voice == 6) {
//                if (sharp == 1) {
//                    Passive_Buzzer_Drum(9);
//                } else {
//                    Passive_Buzzer_Drum(7);
//                }
//                HAL_Delay(70);
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[6 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);  // 清除中断标志
//    }
//}
////
//void EXTI15_10_IRQHandler(void) {
//    // 检查是否为 EXTI11 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET) { // 检查 PA11 状态
//            if (voice == 6) {
//                Passive_Buzzer_Drum(4);
//                HAL_Delay(70);  // 使用 HAL_Delay 替代 Delay_ms
//                Passive_Buzzer_OFF(2);
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[3 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI12 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET) { // 检查 PB12 状态
//            if (voice == 6) {
//                Passive_Buzzer_Drum(1);
//                HAL_Delay(70);
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[0 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI13 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_SET) { // 检查 PB13 状态
//            if (voice == 6) {
//                Passive_Buzzer_Drum(2);
//                HAL_Delay(70);
//            } else {
//                Passive_Buzzer_Reset(1);
//                uint16_t freq = scale[1 + sft] * transpose[tsp] * pow(2, oct) * pow(1.06, sharp);
//                Passive_Buzzer_ON(freq, voiceDuties[voice - 1], 1);
//            }
//        } else {  // 如果松开琴键
//            Passive_Buzzer_OFF(1);
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI10 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) {
//        if (mode == 1 || isPlaying == 1) {  // 仅在音色模式或伴奏播放时
//            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET) { // 检查 PA10 状态
//                oct = 0;  // 将八度设为 0
//            } else {
//                oct = 1;  // 将八度设为 1
//            }
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI15 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) {
//        if (mode == 1 || isPlaying == 1) {  // 仅在音色模式或伴奏播放时
//            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_SET) { // 检查 PB15 状态
//                oct = 2;  // 将八度设为 2
//            } else {
//                oct = 1;  // 将八度设为 1
//            }
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15);  // 清除中断标志
//    }
//
//    // 检查是否为 EXTI14 的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) {
//        if (mode == 1 || isPlaying == 1) {  // 仅在音色模式或伴奏播放时
//            if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_SET) { // 检查 PB14 状态
//                sharp = 1;  // 设置 sharp 为 1
//            } else {
//                sharp = 0;  // 设置 sharp 为 0
//            }
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14);  // 清除中断标志
//    }
//}
