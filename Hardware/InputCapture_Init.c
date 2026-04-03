#include "stm32f10x.h"

//使用TIM3_CH1通道配置
void InputCapture_Init(void)
{
    // 1.开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //2.配置PA6上拉输入
    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
    GPIO_Inistructure.GPIO_Pin = GPIO_Pin_6;                
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_Inistructure); 

    // 3.选择时钟源
    TIM_InternalClockConfig(TIM3);

    // 4.配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    // 5.配置输入比较单元
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;//选择通道1
    TIM_ICInitStructure.TIM_ICFilter=0x0F;         //输入信号滤波
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//上升沿触发
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1 ;    //触发信号分频
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//直连通道输入
    TIM_ICInit(TIM3,&TIM_ICInitStructure);
    
    // 6.配置从模式
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    
    // 7.使能计时器
    TIM_Cmd(TIM3, ENABLE);

}
uint32_t InputCaprture_GetFreq(void)
{
    return (1000000/(TIM_GetCapture1(TIM3)+1));//获取
}