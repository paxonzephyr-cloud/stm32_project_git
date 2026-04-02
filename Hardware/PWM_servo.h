#ifndef __PWM_SERVO_H
#define __PWM_SERVO_H
#include <stdint.h>

void PWM_Init(void);
void PWM_SetCompare2(uint16_t compare2);
void Servo_SetAngle(float Angle);

#endif
