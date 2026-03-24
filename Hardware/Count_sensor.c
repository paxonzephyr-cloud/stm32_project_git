#include "Delay.h"
#include "stm32f10x.h"
/*
函数内容：设置EXTI中断,选择引脚PB14
函数参数：
返回值：
*/

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 1.EXIT,NVIC已经开启时钟

    GPIO_InitTypeDef GPIO_InitStructure; // 2.GPIO输入设置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); // 3.AFIO中断引脚选择,选择引脚接接入EXTI

    EXTI_InitTypeDef EXTI_Initstructure;
    EXTI_Initstructure.EXTI_Line = EXTI_Line14;
    EXTI_Initstructure.EXTI_LineCmd = ENABLE;                      // 4.EXTI边沿设置及控制
    EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;            // 中断模式，用来响应外部外部变化（按键，计数等）
    EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 下降沿触发
    EXTI_Init(&EXTI_Initstructure);

    // 5.设置NVIC
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置抢占优先级n和响应优先级（子优先级）4-n---->

    NVIC_InitTypeDef NVIC_Initsructure;
    NVIC_Initsructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_Initsructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Initsructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Initsructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_Initsructure);
}

uint16_t CountSensor_Get(void)
{
    return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        // 这个方法不好 (但是好用)
        Delay_ms(10);
        // 只有当引脚确实处于低电平时才计数（确认是下降沿后的稳态），提升稳定性
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
        {
            // 下降沿捕获
            CountSensor_Count++;
        }

        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}
