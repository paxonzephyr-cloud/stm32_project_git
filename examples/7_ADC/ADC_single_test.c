#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "ADC_single.h"

uint16_t ADCValue;
float Voltage;

int main(void)
{
    OLED_Init();
    ADC_single_Init();
    OLED_ShowString(1,1,"ADValue:");
    OLED_ShowString(2,1,"Voltage:0.00");
    while (1)
    {
        ADCValue=ADC_GetValue();
        OLED_ShowNum(1,9,ADCValue,4);

        Voltage=(float)ADCValue/4095*3.3;

        OLED_ShowNum(2,9,(uint16_t)Voltage,1);
        OLED_ShowNum(2,11,(uint16_t)(Voltage*100)%100,2);

        Delay_ms(100);
    }
}
