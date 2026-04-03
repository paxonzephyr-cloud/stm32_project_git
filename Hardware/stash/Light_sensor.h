#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H
#include <stdint.h>

void Light_sensor_Init(uint16_t pin);
uint8_t Light_sensor_Read(uint16_t pin);

#endif
