#include "Key.h"                  // Device header

void Key_Init_A(uint16_t pins) {
    // 使能 GPIOA 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置引脚为下拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;                       // 指定引脚
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;           // 设置为输入模式
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;             // 设置为下拉模式
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;      // 设置速度
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);           // 初始化 GPIOA
}

void Key_Init_B(uint16_t pins) {
    // 使能 GPIOB 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // 配置引脚为下拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;                       // 指定引脚
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;           // 设置为输入模式
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;             // 设置为下拉模式
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;      // 设置速度
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);           // 初始化 GPIOB
}

uint8_t Key_Read_A(uint16_t pins) {
    // 读取 GPIOA 指定引脚的输入状态
    return HAL_GPIO_ReadPin(GPIOA, pins) == GPIO_PIN_SET ? 1 : 0;
}

uint8_t Key_Read_B(uint16_t pins) {
    // 读取 GPIOB 指定引脚的输入状态
    return HAL_GPIO_ReadPin(GPIOB, pins) == GPIO_PIN_SET ? 1 : 0;
}


/**
  * @brief  变量增加函数，可与Key_Read函数配合使用
  * @param  var：需要增加的变量值
  * @param  step：增加的步长，负数表示减少
  * @param  max：变量的最大值
  * @param  set：变量超过最大值后设置的新值
  * @retval 新的变量值
  */
int16_t Key_Var_Plus(int16_t var, int8_t step, int16_t max, int16_t set){
	var += step;
	if((step>0 && var>max)||(step<0 && var<max)){
		var = set;
	}
	return var;
}
