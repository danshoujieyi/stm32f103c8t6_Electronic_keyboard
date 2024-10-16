#include "PWM.h"                  // Device header

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void PWM_Init_1(void)
{
    // 使能TIM2和GPIOA时钟
    __HAL_RCC_TIM2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置引脚 PA0 为复用推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_0;               // GPIO引脚配置
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;         // 复用推挽输出模式
    GPIO_InitStructure.Pull = GPIO_NOPULL;             // 无上拉下拉
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;   // 高速
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置定时器 TIM2
    TIM_HandleTypeDef TIM_Handle;
    TIM_Handle.Instance = TIM2;
    TIM_Handle.Init.Prescaler = 719;                  // 使能预分频，72MHz / (719 + 1) = 100kHz
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;  // 向上计数
    TIM_Handle.Init.Period = 99;                       // ARR设置为99，PWM周期为10ms
    TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频
    TIM_Handle.Init.RepetitionCounter = 0;
    TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    //HAL_TIM_Base_Init(&TIM_Handle);
    HAL_TIM_PWM_Init(&TIM_Handle);                     // 初始化定时器

    // 配置PWM输出
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;                // PWM模式1
    sConfigOC.Pulse = 0;                               // 初始占空比为0
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;       // 高电平有效
    //sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;         // 高电平有效
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;        // 关闭快速模式
    HAL_TIM_PWM_ConfigChannel(&TIM_Handle, &sConfigOC, TIM_CHANNEL_1); // 配置通道1

    // 启动PWM信号
    HAL_TIM_Base_Start(&htim2);                // 启动定时器
    HAL_TIM_PWM_Start(&TIM_Handle, TIM_CHANNEL_1);     // 启动PWM信号
}

void PWM_Init_2(void)
{
    // 使能TIM3和GPIOA时钟
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置引脚 PA7 为复用推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = GPIO_PIN_7;                // 配置引脚7
    GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;          // 复用推挽输出
    GPIO_InitStructure.Pull = GPIO_NOPULL;              // 无上下拉电阻
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;     // 设置为低速
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);          // 初始化GPIO

    // 配置TIM3
    TIM_HandleTypeDef TIM_Handle;
    TIM_Handle.Instance = TIM3;                          // 指定TIM3
    TIM_Handle.Init.Prescaler = 719;                     // 720分频，CLK = 72MHz / (719 + 1) = 100kHz
    TIM_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;    // 向上计数
    TIM_Handle.Init.Period = 99;                         // ARR = 100 - 1
    TIM_Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频
    TIM_Handle.Init.RepetitionCounter = 0;
    TIM_Handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    //HAL_TIM_Base_Init(&TIM_Handle);
    HAL_TIM_PWM_Init(&TIM_Handle);                       // 初始化TIM

    // 配置PWM输出
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;                  // PWM模式1
    sConfigOC.Pulse = 0;                                 // 初始占空比
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;         // 高电平有效
    //sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;         // 高电平有效
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;          // 禁用快速模式
    HAL_TIM_PWM_ConfigChannel(&TIM_Handle, &sConfigOC, TIM_CHANNEL_2); // 配置通道2

    // 启动PWM信号
    HAL_TIM_Base_Start(&htim3);                // 启动定时器
    HAL_TIM_PWM_Start(&TIM_Handle, TIM_CHANNEL_2);       // 启动PWM输出
}


void PWM_SetDuty_1(uint16_t duty){
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, duty);
}

void PWM_SetDuty_2(uint16_t duty){
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
}

void PWM_SetFreq_1(uint16_t freq){
	uint16_t psc = 720000/freq - 1;
    htim2.Instance->PSC = psc;              // 更新TIM2的预分频寄存器
    __HAL_TIM_SET_PRESCALER(&htim2, psc);     // 使用HAL宏设置新的预分频值
    HAL_TIM_Base_Start(&htim2);                // 启动定时器
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void PWM_SetFreq_2(uint16_t freq){
	uint16_t psc = 720000/freq - 1;
    htim3.Instance->PSC = psc;              // 更新TIM2的预分频寄存器
    __HAL_TIM_SET_PRESCALER(&htim3, psc);     // 使用HAL宏设置新的预分频值
    HAL_TIM_Base_Start(&htim3);                // 启动定时器
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
}
