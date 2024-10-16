#ifndef __BUZZER_H
#define __BUZZER_H

#include "stm32f1xx_hal.h"                  // Device header
#include "PWM.h"
#include "stdint.h"

void Passive_Buzzer_Init(void);
void Passive_Buzzer_OFF(uint8_t channel);
void Passive_Buzzer_ON(uint16_t freq, uint8_t tone, uint8_t channel);
void Passive_Buzzer_Timing(uint16_t freq, uint16_t timing, uint8_t tone, uint8_t channel);
void Passive_Buzzer_Reset(uint8_t channel);
void Passive_Buzzer_Drum(uint16_t type);

#endif
