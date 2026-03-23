#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"

int main(void)
{
    OLED_Init();
    OLED_Clear();
    OLED_ShowString(1, 1, "Hello, World!");
    OLED_ShowNum(2, 1, 12345, 5);
    OLED_ShowBinNum(3, 1, 0xAA55, 16);
    OLED_ShowHexNum(4, 1, 0x1234, 16);

    while (1)
    {
    }
}
