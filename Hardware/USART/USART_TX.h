#ifndef __USART_TX_H
#define __USART_TX_H
#include "stm32f10x.h"

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t number);
void Serial_Printf(char* format,...);


#endif

