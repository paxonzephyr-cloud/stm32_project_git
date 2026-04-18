#ifndef __USART_PACKET_HEX_H
#define __USART_PACKET_HEX_H
#include "stm32f10x.h"

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[4];

void Serial_Packet_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t number);
void Serial_Printf(char* format,...);

uint8_t Serial_GetRxData(void);
uint8_t Serial_GetRXFlag(void);

void Serial_SendPacket(void);



#endif

