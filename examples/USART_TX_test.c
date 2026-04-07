#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "USART_TX.h"

int main(void)
{
    OLED_Init();
    Seria_Init();

    // Serial_SendByte(0x41);
    Serial_SendByte('A');


     
    while (1)
    {
    }
}

