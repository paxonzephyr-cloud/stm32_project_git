#include "stm32f10x.h" // Device headerc

extern uint16_t AD_Value[4];

void DMA_ADC_multi_Init(void)
{
    //1.开启时钟,配置ADC时钟分频
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC频率最大为14MHz---72M/6=12M,72M/8=9M
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    //2.配置PA0,PA1,PA2,PA3为模拟输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //3.多路开关
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);

    //4.配置ADC转换器
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;                     //工作模式:ADC1,2独立工作
    ADC_InitStructure.ADC_ScanConvMode=ENABLE;                          //多通道扫描模式:是
    ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;                    //连续转换扫描:是
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //外部触发方式:否(选择软件触发)
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;                //数据对齐方式:右对齐
    ADC_InitStructure.ADC_NbrOfChannel=4;                               //扫描的通道数
    ADC_Init(ADC1,&ADC_InitStructure);

    //配置DMA结构体
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;                //外设(存储器)地址
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;   //按半字发送(DR寄存器低16位是ADC1,高16位是ADC2)
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;       //地址不变
    DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)AD_Value;                     //存储器(外设)地址
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;   //按字节接收
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;           //地址自增
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                //发送方向
    DMA_InitStructure.DMA_BufferSize=4;                          //发送次数
    DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                     //模式:循环循环
    DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                       //:软件触发
    DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;             //优先级
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);//外设图中ADC1的硬件触发只接在Channel1上
   
    DMA_Cmd(DMA1_Channel1,ENABLE);
    ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);

    //5.1 ADC自校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);//完成后返回SET
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1)==SET);//完成后返回SET
    
    //7.软件开启
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
