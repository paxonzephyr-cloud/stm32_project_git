#include "Delay.h"
#include "LED.h"
#include "stm32f10x.h" // Device header
#include "Key.h"

int main(void)
{
    led_in PA0={GPIOA,GPIO_Pin_0,0};
    led_in PA1={GPIOA,GPIO_Pin_1,0};

    LED_Init(&PA0);
    LED_Init(&PA1);

    key_in PB[]={
        {GPIOB,GPIO_Pin_0},
        {GPIOB,GPIO_Pin_11},
    };
    KEY_Init(&PB[0]);
    KEY_Init(&PB[1]);

    while (1){
       if(KEY_GetNum(&PB[0])){
        LED_Toggle(&PA0);
       }
       if(KEY_GetNum(&PB[1])){
        LED_Toggle(&PA1);
       }
    }
}
