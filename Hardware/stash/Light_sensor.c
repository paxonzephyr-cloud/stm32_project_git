#include "stm32f10x.h"

/*
函数内容：初始化按键引脚PB,上拉输入模式,默认高电平
函数参数：引脚pin
返回值：
*/
void Light_sensor_Init(uint16_t pin)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入模式,传感器当前默认输出高电平
    GPIO_Inistructure.GPIO_Pin = pin;            // 引脚
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_Inistructure);
}

uint8_t Light_sensor_Read(uint16_t pin)
{
    return GPIO_ReadInputDataBit(GPIOB, pin);
}
