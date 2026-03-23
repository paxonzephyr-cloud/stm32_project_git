#ifndef __BUZZER_H
#define __BUZZER_H
#include <stdint.h>
void Buzzer_Init(uint16_t pin);
void Buzzer_ON(uint16_t pin);
void Buzzer_OFF(uint16_t pin);
void Buzzer_Toggle(uint16_t pin);
#endif
