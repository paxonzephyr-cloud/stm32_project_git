#include "stm32f10x.h"

void ADC_multi_Init(void)
{
    //1.开启时钟,配置ADC时钟分频
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC频率最大为14MHz---72M/6=12M,72M/8=9M

    //2.配置PA0为模拟输入
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //4.配置ADC转换器
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;                     //工作模式:ADC1,2独立工作
    ADC_InitStructure.ADC_ScanConvMode=DISABLE;                          //多通道扫描模式:否(单词扫描)
    ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;                    //连续转换扫描:否(单次转换)
    ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //外部触发方式:否(选择软件触发)
    ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;                //数据对齐方式:右对齐
    ADC_InitStructure.ADC_NbrOfChannel=1;                               //扫描的通道数(非扫描模式下只有序列1的有效)
    ADC_Init(ADC1,&ADC_InitStructure);

    //5.使能ADC
    ADC_Cmd(ADC1,ENABLE);

    //5.1 ADC自校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)==SET);//完成后返回SET
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1)==SET);//完成后返回SET
    
}

uint16_t ADC_GetValue_2(uint8_t ADC_Channel)
{
     //3.多路开关
    ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//等待ADC转换完成
    return ADC_GetConversionValue(ADC1);            //读取完后会自动清除标志位,不用手动清除
}