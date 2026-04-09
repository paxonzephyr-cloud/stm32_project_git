#include "Delay.h"
#include "LED.h"
#include "stm32f10x.h" // Device header


int main(void)
{
    led_in leds[]={
        {GPIOA,GPIO_Pin_0,0},
        {GPIOA,GPIO_Pin_1,0},
        {GPIOA,GPIO_Pin_2,0},
        {GPIOA,GPIO_Pin_3,0},
        {GPIOA,GPIO_Pin_4,0},
        {GPIOA,GPIO_Pin_5,0},
        {GPIOA,GPIO_Pin_6,0},
        {GPIOA,GPIO_Pin_7,0},
    };

    for (uint8_t i = 0; i < 7; i++)
    {
        LED_Init(&leds[i]);
    }
    
    while (1){
        for (uint8_t i = 0; i < 7; i++)
        {
            LED_ON(&leds[i]);
            Delay_ms(500);
            LED_OFF(&leds[i]);
        }        
    }
}
