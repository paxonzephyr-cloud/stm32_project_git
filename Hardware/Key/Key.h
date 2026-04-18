#ifndef __KEY_H
#define __KEY_H
#include <stdint.h>
#include "stm32f10x.h"

typedef struct{
    GPIO_TypeDef* gpio;
    uint16_t pin;
}key_in;

typedef enum{
    IDLE,               //闲置状态
    Debounce_pressed,   //检测是否真正按下(软件消抖)
    Wait_released,      //等待释放(按键按下不放)
    Debounce_released   //检测是否真正释放
}KeyState;

void KEY_Init(key_in* me);
uint8_t KEY_GetState(key_in* me);
#endif
