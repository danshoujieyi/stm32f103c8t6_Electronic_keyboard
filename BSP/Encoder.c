#include "Encoder.h"                  // Device header

int8_t Encoder_Count = 0;

//void Encoder_Init(void) {
//    // 使能 GPIOB 和 AFIO 时钟
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_AFIO_CLK_ENABLE();
//
//    // 配置引脚 PB10 和 PB11 为上拉输入
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11;    // 配置引脚 10 和 11
//    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;              // 设置为输入模式
//    GPIO_InitStructure.Pull = GPIO_PULLUP;                  // 设置为上拉模式
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;        // 设置速度为高速
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);              // 初始化 GPIOB
//
//    // 配置 EXTI 行
//    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);            // 设置 EXTI 线 10-15 的中断优先级
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);                     // 使能 EXTI 线 10-15 的中断
//
//    // 连接引脚到 EXTI
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);                  // 清除 PB10 的外部中断标志
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);                  // 清除 PB11 的外部中断标志
//
//    // 配置外部中断触发模式
//    // 使用降沿触发
//    EXTI_ConfigTypeDef EXTI_InitStructure;
//
//    // 配置 PB10 的外部中断
//    EXTI_InitStructure.Line = EXTI_LINE_10;                 // 设置外部中断线路为10
//    EXTI_InitStructure.LineCmd = ENABLE;                    // 启用外部中断
//    EXTI_InitStructure.Mode = EXTI_MODE_INTERRUPT;          // 中断模式
//    EXTI_InitStructure.Trigger = EXTI_TRIGGER_FALLING;      // 设置为下降沿触发
//    HAL_EXTI_Config(&EXTI_InitStructure);                   // 配置外部中断
//
//    // 配置 PB11 的外部中断
//    EXTI_InitStructure.Line = EXTI_LINE_11;                 // 设置外部中断线路为11
//    HAL_EXTI_Config(&EXTI_InitStructure);                   // 配置外部中断
//}



int8_t Encoder_Get(void){
	return Encoder_Count;
}

void Encoder_Clear(void){
	Encoder_Count = 0;
}

/**
  * @brief  通过旋转编码器控制变量值的函数
  * @param  var：需要控制的变量值
  * @param  step：控制的步长，负数可反转旋转的方向
  * @param  min：变量的最小值
  * @param  max：变量的最大值
  * @param  setL：变量超过最小值后设置的新值
  * @param  setH：变量超过最大值后设置的新值
  * @retval 新的变量值
  */
int16_t Encoder_Var(int16_t var, int8_t step, int16_t min, int16_t max, int16_t setL, int16_t setH){
	var += Encoder_Get()*step;
	if(var > max){
		var = setH;
	}
	else if(var < min){
		var = setL;
	}
	Encoder_Clear();
	return var;
}

//void EXTI15_10_IRQHandler(void) {
//    // 检查是否为EXTI10的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET) { // 检查PB11状态
//            Encoder_Count = 1;  // 计数增加
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);  // 清除中断标志
//    }
//
//    // 检查是否为EXTI11的中断
//    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) {
//        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET) { // 检查PB10状态
//            Encoder_Count = -1; // 计数减少
//        }
//        __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);  // 清除中断标志
//    }
//}
