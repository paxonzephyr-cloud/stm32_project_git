#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "InputCapture_Init.h"
#include "InputCapture_PWM_Init.h"

int main(void)
{
    OLED_Init();

    //初始化,使其输出一个占空比50,频率1k的PWM方波
    InputCapture_PWM_Init();
    PWM_SetCompare1(80);              //d=ccr/100
    PWM_SetPrescaler(7200-1);        //freq=72M/720-1/100

    InputCapture_Init();
    OLED_ShowString(1,1,"Freq:00000Hz");
    OLED_ShowString(2,1,"Duty:00%");

    while (1)
    {
        OLED_ShowNum(1,6,InputCaprture_GetFreq(),5);
        OLED_ShowNum(2,6,InputCaprture_GetDuty(),2);
    }
}