#include "stm32f10x.h" // Device header

/*
函数内容：初始化LED引脚GPIO
函数参数：引脚pin
返回值：
*/
void LED_Init(uint16_t pin)
{
    static uint8_t clock_enabled = 0;

    // 只使能一次时钟
    if (!clock_enabled)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        clock_enabled = 1;
    }

    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出模式
    GPIO_Inistructure.GPIO_Pin = pin;                // 引脚
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度

    GPIO_Init(GPIOA, &GPIO_Inistructure); // 初始化后默认开启LED

    GPIO_SetBits(GPIOA, pin); // 关闭led灯
}

/*
函数内容：点亮LED
函数参数：引脚pin
返回值：
*/
void LED_ON(uint16_t pin)
{
    GPIO_ResetBits(GPIOA, pin);
}

/*
函数内容：熄灭LED
函数参数：引脚pin
返回值：
*/
void LED_OFF(uint16_t pin)
{
    GPIO_SetBits(GPIOA, pin);
}

/*
函数内容：翻转LED
函数参数：引脚pin
返回值：
*/
void LED_Toggle(uint16_t pin)
{
    // static uint16_t last_state = 0;如果多个pin调用会相互干扰

    // last_state = GPIO_ReadOutputDataBit(GPIOA, pin);
    if (GPIO_ReadOutputDataBit(GPIOA, pin) == Bit_RESET)
    {
        GPIO_SetBits(GPIOA, pin);
    }
    else
        GPIO_ResetBits(GPIOA, pin);
}