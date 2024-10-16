#include "stm32f1xx_hal.h"                  // Device header
#include "AD.h"

void JoyStick_Init(void) {
    // 使能 GPIOA 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置引脚 PA1 为上拉输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_1;                // 配置引脚 1
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;          // 设置为输入模式
    GPIO_InitStructure.Pull = GPIO_PULLUP;              // 设置为上拉模式
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    // 设置速度为高速
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);          // 初始化 GPIOA

    // 初始化 ADC 引脚（假设 AD_Init 函数已定义为 HAL 风格，如 GPIOA 的 3 和 5 引脚）
    AD_Init(GPIO_PIN_3 | GPIO_PIN_5);                   // 使用 HAL 进行 ADC 初始化
}


// 获取摇杆开关状态
uint8_t JoyStick_GetSW(void) {
    // 读取PA1引脚状态
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET) {
        return 0; // 如果 PA1 为高电平，返回 0（未按下）
    }
    return 1; // 否则返回 1（按下）
}

// 获取搓摇杆的 X 值
uint16_t JoyStick_GetX(void) {
    return AD_GetValue(ADC_CHANNEL_5); // 调用 AD_GetValue 函数获取 ADC_Channel_5 的值
}

// 获取搓摇杆的 Y 值
uint16_t JoyStick_GetY(void) {
    return AD_GetValue(ADC_CHANNEL_3); // 调用 AD_GetValue 函数获取 ADC_Channel_3 的值
}
