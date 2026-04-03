#ifndef __INPUTCAPTURE_PWM_H
#define __INPUTCAPTURE_PWM_H
#include <stdint.h>

void InputCapture_PWM_Init(void);
void PWM_SetCompare1(uint16_t compare1);
void PWM_SetPrescaler(uint16_t Prescaler);

#endif
