#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
#include "stm32f10x.h"

typedef struct{
    GPIO_TypeDef* gpio;
    uint16_t pin;
}key_in;
void KEY_Init(key_in* me);
uint8_t KEY_GetNum(key_in* me);
#endif
