#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
void KEY_Init(uint16_t pin);
uint8_t KEY_GetNum_2(uint16_t pin);
uint16_t KEY_GetNum(uint16_t pin);
#endif
