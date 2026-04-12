#ifndef __MYSPI_H
#define __MYSPI_H
#include "stm32f10x.h" // Device header
#include "Delay.h"

typedef enum{
    LOW,
    HIGH,
}state;
void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_Swap(uint8_t ByteSend);

void MySPI_W_SS(state BitValue);
void MySPI_W_SCK(state BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);

#endif
