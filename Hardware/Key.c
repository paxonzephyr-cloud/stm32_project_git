#include "Delay.h"
#include "stm32f10x.h"

/*
函数内容：初始化按键引脚PB,默认上拉输入
函数参数：引脚pin
返回值：
*/
void KEY_Init(uint16_t pin)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_Inistruction;
    GPIO_Inistruction.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Inistruction.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Inistruction.GPIO_Pin = pin;

    GPIO_Init(GPIOB, &GPIO_Inistruction);
}

/*
函数内容：检测对应引脚的按键是否按下
函数参数：引脚pin
返回值：按下并松开的按键(优先级从低位开始)
*/
uint16_t KEY_GetNum(uint16_t pin)
{
    uint16_t input_state = GPIO_ReadInputData(GPIOB);
    uint16_t pressed_pin = ((~input_state) & pin); // 检测按下了哪些按键,是否是检测的引脚

    if (pressed_pin != 0)
    {
        Delay_ms(20);
        uint16_t input_state = GPIO_ReadInputData(GPIOB);
        uint16_t pressed_pin = ((~input_state) & pin); // 二次读取

        if (pressed_pin != 0)
        {
            // 获取具体触发了哪个位（优先级处理）
            uint16_t actual_pin = 0;
            for (int i = 0; i < 16; i++)
            {
                if (pressed_pin & (1 << i)) // 如果是pin & 那么结果检测的是输入的参数有哪些引脚,根据优先级,只能输出引脚中最低的那一位
                {
                    actual_pin = (1 << i);
                    break; // 找到第一个按下的就跳出
                }
            }

            // 等待按下的按键释放,而不是检测的所有按键(pin脚)
            // 这样如果你按住 Pin1 的同时去按 Pin11，逻辑才不会打架
            // while ((~GPIO_ReadInputData(GPIOB) & actual_pin) == 0)
            // ;
            // while (pressed_pin != 0) // 等待所有按下的按键释放
            //     ;

            while (GPIO_ReadInputDataBit(GPIOB, actual_pin) == Bit_RESET)
                ;

            Delay_ms(20);//松开防抖,防止松开按键时,因为抖动再次误判为按下导致两次返回

            return actual_pin;
        }
    }
    return 0; // 没有按键按下则返回0
}

uint8_t KEY_GetNum_2(uint16_t pin)
{
    uint8_t KeyNum = 0;

    if (GPIO_ReadInputDataBit(GPIOB, pin) == 0)
    {
        Delay_ms(20);

        while (GPIO_ReadInputDataBit(GPIOB, pin) == 0)
            ; // 等待按键释放,防止按键一直被按着

        Delay_ms(20);
        KeyNum = 1;
    }
    return KeyNum;
}

// deepseek
#define KEY_PRESSED 0 // 假设低电平有效
#define KEY_RELEASED 1

uint8_t Key_Scan(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    static uint8_t key_state = KEY_RELEASED;
    uint8_t key_num = 0;

    // 读取当前按键状态
    uint8_t current_state = GPIO_ReadInputDataBit(GPIOx, pin);

    switch (key_state)
    {
    case KEY_RELEASED:
        if (current_state == KEY_PRESSED) // 检测到按下
        {
            Delay_ms(20);                                         // 消抖
            if (GPIO_ReadInputDataBit(GPIOx, pin) == KEY_PRESSED) // 确认按下
            {
                key_state = KEY_PRESSED;
            }
        }
        break;

    case KEY_PRESSED:
        if (current_state == KEY_RELEASED) // 检测到释放
        {
            Delay_ms(20);                                          // 消抖
            if (GPIO_ReadInputDataBit(GPIOx, pin) == KEY_RELEASED) // 确认释放
            {
                key_state = KEY_RELEASED;
                key_num = 1; // 一次完整的按键动作
            }
        }
        break;
    }

    return key_num;
}