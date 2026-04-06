#include "stm32f10x.h" // Device header

uint32_t M2M_SIZE;

void DMA_M2M_Init(uint32_t Addra,uint32_t Addrb,uint32_t SIZE)
{
    M2M_SIZE=SIZE;
    //1.开启时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

    //配置DMA结构体
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr=Addra;                //外设(存储器)地址
    DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;//按字节发送
    DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Enable;       //地址自增
    DMA_InitStructure.DMA_MemoryBaseAddr=Addrb;                     //存储器(外设)地址
    DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;   //按字节接收
    DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;           //地址自增
    DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                //发送方向
    DMA_InitStructure.DMA_BufferSize=M2M_SIZE;                          //发送次数
    DMA_InitStructure.DMA_Mode=DMA_Mode_Normal;                     //模式:正常缓存(非循环)
    DMA_InitStructure.DMA_M2M=DMA_M2M_Enable;                       //:软件触发
    DMA_InitStructure.DMA_Priority=DMA_Priority_Medium;             //优先级
    DMA_Init(DMA1_Channel1,&DMA_InitStructure);

    //3.开启DMA通道
    DMA_Cmd(DMA1_Channel1,DISABLE);

}

void DMA_M2M_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1,M2M_SIZE);
    DMA_Cmd(DMA1_Channel1,ENABLE);

    while(DMA_GetFlagStatus(DMA1_FLAG_TC1)==RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}