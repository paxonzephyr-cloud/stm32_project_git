#include "Delay.h"
#include "OLED.h"
#include "PWM_servo.h"
#include "stm32f10x.h" // Device header

int main(void)
{
    PWM_Init();
    PWM_SetCompare2(500);

    while (1)
    {

    }
}
