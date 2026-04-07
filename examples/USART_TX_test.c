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

    Serial_SendByte(0x41);

    Serial_SendArray(MyArray,4);
     
    Seria_SendString("\r\nNUM1=");

    Seria_SendNumber(123);

    printf("\r\nNUM2=%d",222);

    char String[100];
    sprintf(String,"\r\nNUM3=%d",333);
    Seria_SendString(String);

    Serial_Printf("\r\nNUM=%d",444);

    Serial_Printf("\r\n你好世界");

    while (1)
    {
    }
}

