#include "LED.h"

void LED_Init(led_in* me)
{
    if      (me->gpio == GPIOA) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (me->gpio == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (me->gpio == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出模式
    GPIO_Inistructure.GPIO_Pin = me->pin;                // 引脚
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度

    GPIO_Init(me->gpio, &GPIO_Inistructure); // 初始化后默认开启LED

    switch (me->state)
    {
    case 0:
        GPIO_SetBits(me->gpio,me->pin);
        break;
    case 1:
        GPIO_ResetBits(me->gpio,me->pin);
        break;
    }
}

void LED_ON(led_in* me)
{
    GPIO_ResetBits(me->gpio,me->pin);
}

void LED_OFF(led_in* me)
{
    GPIO_SetBits(me->gpio,me->pin);
}

void LED_Toggle(led_in* me)
{
    me->gpio->ODR ^= me->pin;
    // if(GPIO_ReadOutputDataBit(me->gpio,me->pin)==Bit_SET){
    // GPIO_ResetBits(me->gpio,me->pin);
    // }else {
    // GPIO_SetBits(me->gpio,me->pin);
    // }

    // if((me->gpio->ODR & me->pin) != (uint32_t)Bit_RESET){//检查是否为高电平
    //     me->gpio->BRR = me->pin;        
    // } else{
    //     me->gpio->BSRR = me->pin;
    // }
}