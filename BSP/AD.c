#include "stm32f1xx_hal.h"                  // Device header
#include "adc.h"
#include "main.h"
void AD_Init(uint16_t pins) {
    // 使能 ADC1 和 GPIOA 时钟
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置 GPIO 引脚为模拟输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;                     // 指定引脚
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;        // 设置为模拟模式
    GPIO_InitStructure.Pull = GPIO_NOPULL;             // 不使用上拉或下拉电阻
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);         // 初始化 GPIOA

    // ADC 初始化
    ADC_HandleTypeDef hadc1;
    hadc1.Instance = ADC1;                              // 指定 ADC1
    //hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV6; // 设置 ADC 预分频
    //hadc1.Init.Resolution = ADC_RESOLUTION_12B;        // 设置分辨率为12位
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;        // 禁用扫描模式
    hadc1.Init.ContinuousConvMode = DISABLE;           // 禁用连续转换
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;  // 软件启动转换
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;       // 数据右对齐
    hadc1.Init.NbrOfConversion = 1;                    // 转换通道数
    HAL_ADC_Init(&hadc1);                              // 初始化 ADC

    // 开始 ADC 校准
    //HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET); // 校准 ADC
}

uint16_t AD_GetValue(uint8_t ADC_Channel) {
    ADC_ChannelConfTypeDef sConfig = {0}; // 创建配置结构体

    // 配置指定的 ADC 通道
    sConfig.Channel = ADC_Channel;                     // 设置通道
    sConfig.Rank = 1;                                 // 设置转化顺序为 1
    sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5; // 设置采样时间
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);         // 配置 ADC 通道

    HAL_ADC_Start(&hadc1);                            // 启动 ADC 转换
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // 等待转换结束

    return HAL_ADC_GetValue(&hadc1);                  // 获取转换值
}
