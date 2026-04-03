#include "stm32f10x.h"

void PWM_LEDbreath_Init(void)
{
    // 1.开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //1.1重映射引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //根据复用映射表来决定的
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
    //解除jetec复用
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    //2.配置PA0为复用推挽输出----由外设直接控制输出
    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_AF_PP; 
    GPIO_Inistructure.GPIO_Pin = GPIO_Pin_15;                
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_Inistructure); 

    // 3.选择时钟源
    TIM_InternalClockConfig(TIM2);

    // 4.配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    // 5.配置输出比较单元
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;                 //输出比较模式(冻结,置电平,翻转,pwm)
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;        //输出比较极性
    TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;   //输出使能
    TIM_OCInitStructure.TIM_Pulse=0;                             //设置CCR
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);
   
    // 6.使能计时器
    TIM_Cmd(TIM2, ENABLE);

}

void PWM_SetCompare1(uint16_t compare1)
{
    TIM_SetCompare1(TIM2,compare1);
}