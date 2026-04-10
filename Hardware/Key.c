#include "Delay.h"
#include "Key.h"
/**
 * @brief 初始化按键
 * @param key_in* me
 * @return none  
 */
void KEY_Init(key_in* me)
{
    if      (me->gpio == GPIOA) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (me->gpio == GPIOB) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (me->gpio == GPIOC) RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_Inistruction;
    GPIO_StructInit(&GPIO_Inistruction);
    GPIO_Inistruction.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Inistruction.GPIO_Pin = me->pin;

    GPIO_Init(me->gpio, &GPIO_Inistruction);
}

/**
 * @brief 检测按键是否按下
 * @param key_in* me
 * @return  1/0 按下返回1
 */
uint8_t KEY_GetNum(key_in* me)
{
    uint8_t key_state=GPIO_ReadInputDataBit(me->gpio,me->pin);

    if (key_state == 0) {

        Delay_ms(20);
        key_state=GPIO_ReadInputDataBit(me->gpio,me->pin);

        if (key_state == 0) {
        
            while (GPIO_ReadInputDataBit(me->gpio, me->pin) == Bit_RESET);//等待松开

            Delay_ms(20);//松开防抖,防止松开按键时,因为抖动再次误判为按下导致两次返回

            return 1;
        }
    }
    return 0; // 按键没有按下则返回0
}

