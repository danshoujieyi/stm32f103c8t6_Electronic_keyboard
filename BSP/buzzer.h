//
// Created by ���ο� on 24-9-19.
//

#ifndef C8T6_BALANCE_BUZZER_H
#define C8T6_BALANCE_BUZZER_H

#include "stm32f1xx_hal.h" // �������ľ���оƬѡ����ʵ�HALͷ�ļ�

// �����������������
#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_PIN_2


// ����ԭ��
void Buzzer_Init(void);  // ��ʼ������������
void Buzzer_On(void);    // �򿪷�����
void Buzzer_Off(void);   // �رշ�����
void Buzzer_Alarm(int distance); // distance Ϊ��������

#endif //C8T6_BALANCE_BUZZER_H
