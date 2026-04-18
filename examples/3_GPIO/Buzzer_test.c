#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "Buzzer.h"
#include "Light_sensor.h"

int main(void)
{
    Buzzer_Init(GPIO_Pin_12);
    Light_sensor_Init(GPIO_Pin_13);

    while (1)
    {

        if (Light_sensor_Read(GPIO_Pin_13) == Bit_SET) // 传感器输出高电平时点亮LED
        {
            Buzzer_ON(GPIO_Pin_12);
        }
        else
        {
            Buzzer_OFF(GPIO_Pin_12);
        }
    }
}
