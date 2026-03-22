#ifndef __LED_H
#define __LED_H
#include <stdint.h>

void LED_Init(uint16_t pin);
void LED_ON(uint16_t pin);
void LED_OFF(uint16_t pin);
void LED_Toggle(uint16_t pin);

#endif
