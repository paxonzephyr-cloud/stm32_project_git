#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "Timer_gpio_etr.h"
uint16_t NUM;
int main(void)
{
    OLED_Init();
    OLED_ShowString(1, 1, "NUM:");
    OLED_ShowString(2, 1, "CNT:");
    Timer_Init();

    while (1)
    {
        OLED_ShowNum(1, 5, NUM, 5);
        OLED_ShowNum(2, 5, TIM_GetCounter(TIM2), 5);
    }
}
