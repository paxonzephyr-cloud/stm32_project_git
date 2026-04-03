#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "Encoder_Interface.h"
#include "OLED.h"
#include "Timer_Clock.h"

int16_t Speed;
int main(void)
{
    OLED_Init();
    Encoder_Interface_Init();
    Timer_Clock_Init();

    OLED_ShowString(1, 1, "CNT:");
    while (1)
    {
        OLED_ShowSignedNum(1, 7, Speed, 5);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update))
    {
        Speed=Encoder_Interface_Get();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}