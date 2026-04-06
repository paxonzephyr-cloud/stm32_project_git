#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"

uint8_t aa=0x66;
const uint8_t bb=0x66;

#define ADC1_DR (uint32_t)0x4001244C

int main(void)
{
    OLED_Init();

    // OLED_ShowHexNum(1,1,aa,4);
    // OLED_ShowHexNum(2,1,(uint32_t)&aa,8);       //2000:在SRAM

    // OLED_ShowHexNum(3,1,bb,4);
    // OLED_ShowHexNum(4,1,(uint32_t)&bb,8);       //0800:在Flash(还有程序代码的内容)

    OLED_ShowHexNum(3,1,(uint32_t)&(ADC1->DR),8);       //4000:

    OLED_ShowHexNum(4,1,ADC1_DR,8);       //直接定义物理地址

    while (1)
    {

    }
}
