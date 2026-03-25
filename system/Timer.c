#include "stm32f10x.h"
/**
 * @brief 使用内部时钟RCC配置TIM2
 * @param none  
 * @return none  
 */
extern uint16_t NUM;
void Timer_Init(void)
{
    //1.开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    //2.选择时钟源
    TIM_InternalClockConfig(TIM2);

    //3.配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=0;      //这个过滤器设置了其实很好用
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=7200-1;       //72M/7200/10000=1hz
    TIM_TimeBaseInitStructure.TIM_Prescaler=10000-1;     //这样1s产生一次中断
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    //预分频器是有缓冲寄存器,设置的值只有在更新事件时才会起作用,为了立即起效,配置完会\
    生成一个更新事件---->更新事件和更新中断同时发生,更新中断会置更新中断标志位\进而在上电后立即进入中断函数
    //解决办法:配置完后清除更新中断标志位
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);


    //4.使能更新中断
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    //5.配置NVIC
    
    //配置优先级(全局的)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //配置外设通道并使能,设置抢断和响应优先级
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_Init(&NVIC_InitStructure);

    //6.使能计时器
    TIM_Cmd(TIM2,ENABLE);

}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)) {

        NUM+=1;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }

}