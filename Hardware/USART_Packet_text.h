#ifndef __USART_PACKET_TEXT_H
#define __USART_PACKET_TEXT_H
#include "stm32f10x.h"

extern uint8_t Serial_TxPacket[];
extern char  Serial_RxPacket[4];
extern uint8_t RxData;

void Serial_Packet_text_Init(void);

void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t length);
void Seria_SendString(char* String);
void Seria_SendNumber(uint32_t number);
void Serial_Printf(char* format,...);

uint8_t Serial_GetRxData(void);
uint8_t Serial_GetRXFlag(void);


#endif

