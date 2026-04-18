#include "stm32f10x.h"
#include "Buzzer.h"
/*
函数内容：初始化蜂鸣器引脚PB,低电平触发,默认关闭
函数参数：引脚pin
返回值：
*/
void Buzzer_Init(uint16_t pin)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_Inistruction;
    GPIO_Inistruction.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Inistruction.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Inistruction.GPIO_Pin = pin;

    GPIO_Init(GPIOB, &GPIO_Inistruction);
    GPIO_SetBits(GPIOB, pin); // 默认关闭蜂鸣器
}

/*
函数内容：开启蜂鸣器
函数参数：引脚pin
返回值：
*/
void Buzzer_ON(uint16_t pin)
{
    GPIO_ResetBits(GPIOB, pin);
}

/*
函数内容：关闭蜂鸣器
函数参数：引脚pin
返回值：
*/
void Buzzer_OFF(uint16_t pin)
{
    GPIO_SetBits(GPIOB, pin);
}

/*
函数内容：寄存器操作翻转蜂鸣器
函数参数：引脚pin
返回值：
*/
void Buzzer_Toggle(uint16_t pin)
{

    GPIOB->ODR ^= pin; // 直接操作寄存器翻转状态
    // 如PB12现在是低电平,GPIO->ODR是0x1000
    // 0x0000 ^ 0x1000 = 0x1000
    // ODR被赋值为0x1000,PB12输出高电平
    // 再次调用时,GPIO->ODR是0x1000
    // 0x1000 ^ 0x1000 = 0x0000
    // ODR被赋值为0x0000,PB12输出低电平
}

/*
函数内容：库函数封装翻转蜂鸣器
函数参数：引脚pin
返回值：
*/
void Buzzer_Toggle2(uint16_t pin)
{
    GPIO_WriteBit(GPIOB, pin,
                  (GPIO_ReadOutputDataBit(GPIOB, pin) == Bit_RESET) ? Bit_SET : Bit_RESET);
}
