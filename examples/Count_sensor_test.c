#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "Count_sensor.h"

int main(void)
{
    OLED_Init();
    CountSensor_Init();
    OLED_ShowString(1, 1, "Count:");
    while (1)
    {
        OLED_ShowNum(1, 7, CountSensor_Get(), 5);
    }
}
