#ifndef __USART_PACKET_TEXT_H
#define __USART_PACKET_TEXT_H
#include "stm32f10x.h"

extern char  Serial_RxPacket[4];
extern uint8_t RxData;
extern uint8_t Serial_RxFlag;

void Serial_Packet_text_Init(void);

void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t number);
void Serial_Printf(char* format,...);



#endif

