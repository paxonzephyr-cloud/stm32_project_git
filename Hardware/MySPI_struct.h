#ifndef __MYSPI_STRUCT_H
#define __MYSPI_STRUCT_H
#include "stm32f10x.h" // Device header

typedef enum{
    LOW=0,
    HIGH,
}state;

typedef struct
{
    GPIO_TypeDef *gpio;
    uint16_t      pin;
} SPI_Pin;

typedef struct
{
    SPI_Pin ss;
    SPI_Pin sck;
    SPI_Pin mosi;
    SPI_Pin miso;
} SoftSPI_Config;

void    MySPI_Init (const SoftSPI_Config *cfg);
void    MySPI_Start(void);
void    MySPI_Stop (void);
uint8_t MySPI_Swap (uint8_t ByteSend);

#endif
