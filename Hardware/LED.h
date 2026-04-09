#ifndef __LED_H
#define __LED_H
#include <stdint.h>
#include "stm32f10x.h" // Device header

typedef struct
{
    GPIO_TypeDef* gpio;
    uint16_t pin;
    uint8_t state;
}led_in;

void LED_Init(led_in* me);
void LED_ON(led_in* me);
void LED_OFF(led_in* me);
void LED_Toggle(led_in* me);

#endif
