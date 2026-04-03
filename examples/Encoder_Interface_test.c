#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "Encoder_Interface.h"
#include "OLED.h"


int main(void)
{
    OLED_Init();
    Encoder_Interface_Init();
    OLED_ShowString(1, 1, "CNT:");
    while (1)
    {
        OLED_ShowSignedNum(1, 5, Encoder_Interface_Get(), 5);
        Delay_ms(1000);
   
    }
}