#include "Key.h"                  // Device header

void Key_Init_A(uint16_t pins) {
    // ʹ�� GPIOA ʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ��������Ϊ��������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;                       // ָ������
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;           // ����Ϊ����ģʽ
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;             // ����Ϊ����ģʽ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;      // �����ٶ�
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);           // ��ʼ�� GPIOA
}

void Key_Init_B(uint16_t pins) {
    // ʹ�� GPIOB ʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // ��������Ϊ��������
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pins;                       // ָ������
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;           // ����Ϊ����ģʽ
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;             // ����Ϊ����ģʽ
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;      // �����ٶ�
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);           // ��ʼ�� GPIOB
}

uint8_t Key_Read_A(uint16_t pins) {
    // ��ȡ GPIOA ָ�����ŵ�����״̬
    return HAL_GPIO_ReadPin(GPIOA, pins) == GPIO_PIN_SET ? 1 : 0;
}

uint8_t Key_Read_B(uint16_t pins) {
    // ��ȡ GPIOB ָ�����ŵ�����״̬
    return HAL_GPIO_ReadPin(GPIOB, pins) == GPIO_PIN_SET ? 1 : 0;
}


/**
  * @brief  �������Ӻ���������Key_Read�������ʹ��
  * @param  var����Ҫ���ӵı���ֵ
  * @param  step�����ӵĲ�����������ʾ����
  * @param  max�����������ֵ
  * @param  set�������������ֵ�����õ���ֵ
  * @retval �µı���ֵ
  */
int16_t Key_Var_Plus(int16_t var, int8_t step, int16_t max, int16_t set){
	var += step;
	if((step>0 && var>max)||(step<0 && var<max)){
		var = set;
	}
	return var;
}
