#include "stm32f10x.h" // Device headerc

void Seria_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_InitTypeDef USART_InitSructure;    
    USART_InitSructure.USART_BaudRate=9600;
    USART_InitSructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//硬件流使能:否,不使用
    USART_InitSructure.USART_Mode=USART_Mode_Tx;                //发送使能
    USART_InitSructure.USART_Parity=USART_Parity_No;            //奇偶校验
    USART_InitSructure.USART_WordLength=USART_WordLength_8b;
    USART_InitSructure.USART_StopBits=USART_StopBits_1;
    USART_Init(USART1,&USART_InitSructure);

    USART_Cmd(USART1,ENABLE);
    
}

void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1,Byte);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
    //关于清除标志位,由于对USART->DR进行写操作时会将TXE标志位清零,所以不用再手动(软件)清除
}

void Serial_SendArray(uint8_t Array[],uint16_t length)
{   
    for (uint16_t i = 0; i < length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

void Seria_SendString(char* String)
{
    while(*String){
        Serial_SendByte(*String);
        String++;
    }
}