#include "Delay.h"
#include "Key.h"
#include "SysTick.h"
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
uint8_t KEY_GetState(key_in* me)
{
    static KeyState state=IDLE;
    static uint32_t last_tick=0;

    switch (state){
        case IDLE:
            if(GPIO_ReadInputDataBit(me->gpio,me->pin)==0){
                last_tick=Get_Tick();
                state=Debounce_pressed;
            }
        break;

        case Debounce_pressed:
        if(Get_Tick()-last_tick>=20){
            if(GPIO_ReadInputDataBit(me->gpio,me->pin)==0){
                state=Wait_released;
            }else state=IDLE;
        }
        break;
        
        case Wait_released:
            if(GPIO_ReadInputDataBit(me->gpio,me->pin)==1){
                last_tick=Get_Tick();
                state=Debounce_released;
            }
        break;          
        
        case Debounce_released:
        if(Get_Tick()-last_tick>=20){
            if(GPIO_ReadInputDataBit(me->gpio,me->pin)==1){
                state=IDLE;
                return 1;
            }else state=Wait_released;
        } 
        break;
    }
   
    return 0;
}

