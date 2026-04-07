#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "USART_TX.h"
#include "stdio.h"

uint8_t MyArray[4]={0x42,0x43,0x44,0x45};
char* MyString="HELLOWORLD";

int main(void)
{
    OLED_Init();
    Seria_Init();

    // Serial_SendByte(0x41);
    // Serial_SendByte('A');

    // Serial_SendArray(MyArray,4);
     
    // Seria_SendString("HELLOWORLD\r\n");

    // Seria_SendNumber(12345);

    printf("NUM=%d",666);
    // printf("HELLOWORLD");

    while (1)
    {
    }
}

