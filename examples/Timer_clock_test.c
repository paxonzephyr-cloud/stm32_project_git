#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "Timer.h"
#include "OLED.h"

uint16_t NUM;
int main(void)
{
    OLED_Init();
    OLED_ShowString(1, 1, "NUM:");

    Timer_Init();

    while (1)
    {
        OLED_ShowNum(1, 5, NUM, 5);
        }
}
