#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "stm32f10x.h" // Device header


int main(void)
{
    LED_Init(GPIO_Pin_1 | GPIO_Pin_2);
    KEY_Init(GPIO_Pin_1 | GPIO_Pin_11);

    while (1)
    {
        uint16_t key = KEY_GetNum(GPIO_Pin_1 | GPIO_Pin_11);
        if (key == GPIO_Pin_1)
        {
            LED_Toggle(GPIO_Pin_1);
        }

        if (key == GPIO_Pin_11)
        {
            LED_Toggle(GPIO_Pin_2);
        }
    }
}
