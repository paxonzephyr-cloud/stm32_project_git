#include "stm32f10x.h" // Device header


void Encoder_Interface_Init(void)
{
// 1.开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //2.配置PA6,PA7为上拉输入
    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入-----与外部电位一致
    GPIO_Inistructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;                
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_Inistructure); 

    // 3.选择时钟源-----没用了
    // TIM_InternalClockConfig(TIM3); 

    // 3.配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//----没作用了
    TIM_TimeBaseInitStructure.TIM_Period = 65536-1;     // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1- 1; // PSC      //影响旋转一格计数的增减量-----1<-->4
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                              //   2<-->2   
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    // 4.配置输入比较单元
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;//选择通道1
    TIM_ICInitStructure.TIM_ICFilter=0x0F;         //输入信号滤波
    // TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//-----后面的Encode也会配置,所以也可省去
    // TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1 ;    //触发信号分频-----不使用所以不需要
    // TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;//直连通道输入
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;//选择通道1
    TIM_ICInitStructure.TIM_ICFilter=0x0F;         //输入信号滤波
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;//上升沿触发
    TIM_ICInit(TIM3,&TIM_ICInitStructure);

    //5.设置编码
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

    //6.开启定时器
    TIM_Cmd(TIM3,ENABLE);
}

int16_t Encoder_Interface_Get(void)
{
    int16_t temp;
    temp=TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return temp;
}