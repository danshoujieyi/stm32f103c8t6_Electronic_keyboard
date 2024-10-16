#include "Passive_Buzzer.h"

void Passive_Buzzer_Init(void){
	PWM_Init_1();
	PWM_Init_2();
}

/**
  * @brief  �������رպ���
  * @param  channel��Ҫ�رյ�ͨ����ţ�����ͨ��ѡ1������ͨ��ѡ2��ͬʱ�ر�ѡ0
  * @retval ��
  */
void Passive_Buzzer_OFF(uint8_t channel){
	if(channel == 0){       // ͨ��1&2
		PWM_SetDuty_1(0);
		PWM_SetDuty_2(0);
	}
	else if(channel == 1){  // ͨ��1
		PWM_SetDuty_1(0);
	}
	else if(channel == 2){  // ͨ��2
		PWM_SetDuty_2(0);
	}
}

/**
  * @brief  �������������������ú���������ֱ���رշ�����
  * @param  freq��������Ƶ��
  * @param  tone����������ɫ����ռ�ձȱ�ʾ
  * @param  channel��Ҫ������ͨ����ţ�����ͨ��ѡ1������ͨ��ѡ2��ͬʱ����ѡ0
  * @retval ��
  */
void Passive_Buzzer_ON(uint16_t freq, uint8_t tone, uint8_t channel){
	if(freq != 0){
		if(channel == 0){       // ͨ��1&2
			PWM_SetFreq_1(freq);
			PWM_SetFreq_2(freq);
			PWM_SetDuty_1(tone);
			PWM_SetDuty_2(tone);
		}
		else if(channel == 1){  // ͨ��1
			PWM_SetFreq_1(freq);
			PWM_SetDuty_1(tone);
		}
		else if(channel == 2){  // ͨ��2
			PWM_SetFreq_2(freq);
			PWM_SetDuty_2(tone);
		}
	}
	else{
        Passive_Buzzer_OFF(channel);
	}
}

/**
  * @brief  ���������������������÷�����ʱ��
  * @param  freq��������Ƶ��
  * @param  timing��������ʱ��
  * @param  tone����������ɫ����ռ�ձȱ�ʾ
  * @param  channel��Ҫ������ͨ����ţ�����ͨ��ѡ1������ͨ��ѡ2��ͬʱ����ѡ0
  * @retval ��
  */
void Passive_Buzzer_Timing(uint16_t freq, uint16_t timing, uint8_t tone, uint8_t channel){
    Passive_Buzzer_ON(freq, tone, channel);
	HAL_Delay(timing);
    Passive_Buzzer_OFF(channel);
}

/**
  * @brief  ���������ú��������ڷ���ǰ����ʹ��ͷ��ƽ��
  * @param  channel��Ҫ���õ�ͨ����ţ�����ͨ��ѡ1������ͨ��ѡ2��ͬʱ����ѡ0
  * @retval ��
  */
void Passive_Buzzer_Reset(uint8_t channel){
	if(channel == 0){       // ͨ��1&2
		PWM_SetFreq_1(1);
		PWM_SetFreq_2(1);
        __HAL_TIM_SET_COUNTER(&htim2, 51);  // ����TIM2������
        __HAL_TIM_SET_COUNTER(&htim3, 51);  // ����TIM3������
	}
	else if(channel == 1){  // ͨ��1
		PWM_SetFreq_1(1);
        __HAL_TIM_SET_COUNTER(&htim2, 51);  // ����TIM2������
	}
	else if(channel == 2){  // ͨ��2
		PWM_SetFreq_2(1);
        __HAL_TIM_SET_COUNTER(&htim3, 51);  // ����TIM3������
	}
}

/**
  * @brief  ����������ֺ���
  * @param  type��������������ͣ�0��ʾ��ֹ��
  * @retval ��
  */
void Passive_Buzzer_Drum(uint16_t type){
		if(type != 0){
            Passive_Buzzer_Reset(2);
		}
	  switch(type){
    case 0:  // ��ֹ��
			HAL_Delay(30);
			break;
    case 1:  // ������
            Passive_Buzzer_Timing(80,30,50,2);
			break;
    case 2:  // С����
			for(int i=0;i<15;i++){
                Passive_Buzzer_ON(600,50,2);
                HAL_Delay(1);
                Passive_Buzzer_ON(1200,30,2);
                HAL_Delay(1);
			}
                Passive_Buzzer_OFF(2);
			break;
    case 3:  // ����պϣ�
            Passive_Buzzer_Timing(3000,30,10,2);
			break;
    case 4:  // ����򿪣�
            Passive_Buzzer_ON(3000,10,2);
              HAL_Delay(30);
			break;
    case 5:  // ͨ�ģ��ߣ�
			for(int i=500;i>470;i--){
                Passive_Buzzer_ON(i,50,2);
                HAL_Delay(1);
			}
            Passive_Buzzer_OFF(2);
			break;
    case 6:  // ͨ�ģ��У�
			for(int i=400;i>370;i--){
                Passive_Buzzer_ON(i,50,2);
                HAL_Delay(1);
			}
              Passive_Buzzer_OFF(2);
			break;
    case 7:  // ͨ�ģ��ͣ�
			for(int i=300;i>270;i--){
                Passive_Buzzer_ON(i,50,2);
                HAL_Delay(1);
			}
              Passive_Buzzer_OFF(2);
			break;
    case 8:  // Agogo���ߣ�
            Passive_Buzzer_Timing(900,30,10,2);
			break;
    case 9:  // Agogo���ͣ�
            Passive_Buzzer_Timing(600,30,10,2);
			break;
  }
}
