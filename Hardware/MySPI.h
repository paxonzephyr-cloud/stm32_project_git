#ifndef __MYSPI_H
#define __MYSPI_H
#include "stm32f10x.h" // Device header
#include "Delay.h"

typedef enum{
    LOW,
    HIGH,
}state;

typedef struct 
{
    GPIO_TypeDef gpio;
    uint16_t pin;
    state BitValue;
}spi_in;

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_Swap(uint8_t ByteSend);

void MySPI_W_SS(state BitValue);
void MySPI_W_SCK(state BitValue);
void MySPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);

//4,5,6,7的初始化是一起配置的,GPIOA这里修改了不够,现在先做一个参考
#define SPI_SS_GPIO     GPIOA
#define SPI_SS_PIN      GPIO_Pin_4

#define SPI_SCK_GPIO    GPIOA
#define SPI_SCK_PIN     GPIO_Pin_5

#define SPI_MOSI_GPIO   GPIOA
#define SPI_MOSI_PIN    GPIO_Pin_7

#define SPI_MISO_GPIO   GPIOA
#define SPI_MISO_PIN    GPIO_Pin_6

#endif
