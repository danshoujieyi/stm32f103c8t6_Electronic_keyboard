#include "Encoder.h"                  // Device header

int8_t Encoder_Count = 0;

//void Encoder_Init(void) {
//    // ʹ�� GPIOB �� AFIO ʱ��
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_AFIO_CLK_ENABLE();
//
//    // �������� PB10 �� PB11 Ϊ��������
//    GPIO_InitTypeDef GPIO_InitStructure;
//    GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11;    // �������� 10 �� 11
//    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;              // ����Ϊ����ģʽ
//    GPIO_InitStructure.Pull = GPIO_PULLUP;                  // ����Ϊ����ģʽ
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;        // �����ٶ�Ϊ����
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);              // ��ʼ�� GPIOB
//
//    // ���� EXTI ��
//    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);            // ���� EXTI �� 10-15 ���ж����ȼ�
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);                     // ʹ�� EXTI �� 10-15 ���ж�
//
//    // �������ŵ� EXTI
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10);                  // ��� PB10 ���ⲿ�жϱ�־
//    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11);                  // ��� PB11 ���ⲿ�жϱ�־
//
//    // �����ⲿ�жϴ���ģʽ
//    // ʹ�ý��ش���
//    EXTI_ConfigTypeDef EXTI_InitStructure;
//
//    // ���� PB10 ���ⲿ�ж�
//    EXTI_InitStructure.Line = EXTI_LINE_10;                 // �����ⲿ�ж���·Ϊ10
//    EXTI_InitStructure.LineCmd = ENABLE;                    // �����ⲿ�ж�
//    EXTI_InitStructure.Mode = EXTI_MODE_INTERRUPT;          // �ж�ģʽ
//    EXTI_InitStructure.Trigger = EXTI_TRIGGER_FALLING;      // ����Ϊ�½��ش���
//    HAL_EXTI_Config(&EXTI_InitStructure);                   // �����ⲿ�ж�
//
//    // ���� PB11 ���ⲿ�ж�
//    EXTI_InitStructure.Line = EXTI_LINE_11;                 // �����ⲿ�ж���·Ϊ11
//    HAL_EXTI_Config(&EXTI_InitStructure);                   // �����ⲿ�ж�
//}



int8_t Encoder_Get(void){
	return Encoder_Count;
}

void Encoder_Clear(void){
	Encoder_Count = 0;
}

/**
  * @brief  ͨ����ת���������Ʊ���ֵ�ĺ���
  * @param  var����Ҫ���Ƶı���ֵ
  * @param  step�����ƵĲ����������ɷ�ת��ת�ķ���
  * @param  min����������Сֵ
  * @param  max�����������ֵ
  * @param  setL������������Сֵ�����õ���ֵ
  * @param  setH�������������ֵ�����õ���ֵ
  * @retval �µı���ֵ
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
//}
