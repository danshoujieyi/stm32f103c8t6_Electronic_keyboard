#include "LED.h"                  // Device header

void LED_Init_A(uint16_t pins) {
    // 使能 GPIOA 时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;  // 无上拉或下拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 速度为高频

    // 初始化 GPIOA
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 设置 pins 高电平
    HAL_GPIO_WritePin(GPIOA, pins, GPIO_PIN_SET);
}

void LED_Init_B(uint16_t pins) {
    // 使能 GPIOB 时钟
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;  // 无上拉或下拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 速度为高频

    // 初始化 GPIOB
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    // 设置 pins 高电平
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_SET);
}

void LED_ON_A(uint16_t pins) {
    // 设置 GPIOA 的引脚为低电平，点亮 LED
    HAL_GPIO_WritePin(GPIOA, pins, GPIO_PIN_RESET);
}

void LED_OFF_A(uint16_t pins) {
    // 设置 GPIOA 的引脚为高电平，熄灭 LED
    HAL_GPIO_WritePin(GPIOA, pins, GPIO_PIN_SET);
}

void LED_ON_B(uint16_t pins) {
    // 设置 GPIOB 的引脚为低电平，点亮 LED
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_RESET);
}

void LED_OFF_B(uint16_t pins) {
    // 设置 GPIOB 的引脚为高电平，熄灭 LED
    HAL_GPIO_WritePin(GPIOB, pins, GPIO_PIN_SET);
}

