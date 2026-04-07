#ifndef __USART_TX_H
#define __USART_TX_H
#include "stm32f10x.h"

void Seria_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t length);
void Seria_SendString(char* String);


#endif

