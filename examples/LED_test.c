#include "Delay.h"
#include "LED.h"
#include "stm32f10x.h" // Device header


int main(void)
{
    led_in PA0={GPIOA,GPIO_Pin_0,0};
    led_in PA1={GPIOA,GPIO_Pin_1,1};
    LED_Init(&PA0);
    LED_Init(&PA1);

    while (1){
       LED_ON(&PA0);
       LED_ON(&PA1);
       Delay_ms(500);
       LED_OFF(&PA0);
       LED_OFF(&PA1);
       Delay_ms(500);
    }
}
