#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "PWM.h"

int main(void)
{
    PWM_Init();
    uint8_t i;
    while (1)
    {
        for ( i = 0; i < 100; i++)
        {
            PWM_SetCompare1(i);
            Delay_ms(20);
        }
        for ( i = 0; i < 100; i++)
        {
            PWM_SetCompare1(100-i);
            Delay_ms(20);

        }
        
    }
}
