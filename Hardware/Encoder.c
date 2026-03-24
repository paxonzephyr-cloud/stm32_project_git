#include "stm32f10x.h"
volatile int16_t Encoder_Count = 0;

void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // EXIT,NVIC已经开启时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    EXTI_InitTypeDef EXTI_Initstructure;
    EXTI_Initstructure.EXTI_Line = EXTI_Line1 | EXTI_Line0;
    EXTI_Initstructure.EXTI_LineCmd = ENABLE;
    EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;     // 中断模式，用来响应外部外部变化（按键，计数等）
    EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_Init(&EXTI_Initstructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_Initsructure;
    NVIC_Initsructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Initsructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Initsructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Initsructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_Initsructure);

    NVIC_Initsructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_Initsructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Initsructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_Initsructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_Initsructure);
}

int16_t Encoder_Get(void)
{
    int16_t count = Encoder_Count;
    Encoder_Count = 0; // 读取后清零，适合增量式编码器的使用场景
    return count;
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) // A下降沿时B为低电平
        {
            Encoder_Count--; // 下降沿捕获
        }

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
        {
            Encoder_Count++; // 下降沿捕获
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}