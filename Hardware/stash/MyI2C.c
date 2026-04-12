#include "MyI2C.h"

void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);
}

void MyI2C_Start(void)
{
    MyI2C_W_SDA(1);//初始化:SDA和SCL空闲时是高电平
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);//在SCL高电平期间SDA变为低电平
    MyI2C_W_SCL(0);//SCL随后也变为低电平
}

void MyI2C_Stop(void)
{
    MyI2C_W_SDA(0);//保证最后SDA在SCL高电平期间是由低电平变为高电平
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);//进入空闲状态:SCL,SDA都是高电平
}

void MyI2C_SendByte(uint8_t Byte)
{
    for (uint8_t i = 0; i < 8; i++){
        MyI2C_W_SCL(0);                 //保证是在SCL低电平期间,主机写入SDA数据
        MyI2C_W_SDA(Byte & (0x80>>i)); //高位先行
        MyI2C_W_SCL(1);                 //写入后SCL转为高电平(从机在此期间读取SDA数据)
    }
    MyI2C_W_SCL(0);  // ✅ 发完8位后，拉低SCL，释放总线控制权给从机
}

uint8_t MyI2C_ReceiveByte(void)
{
//     uint8_t Byte=0x00;    
//     MyI2C_W_SDA(1);

//     for (uint8_t i = 0; i < 8; i++)
//     {    
//         MyI2C_W_SCL(1);
//         if(MyI2C_R_SDA()==1){
//             Byte|=(0x80>>i);
//         }
//         MyI2C_W_SCL(0); 
//     }
//     return Byte;

    MyI2C_W_SCL(0);
    MyI2C_W_SDA(1);  //释放主机对SDA的控制权  // ✅ 不能漏！主机释放SDA，否则从机无法控制总线
    uint8_t Byte=0;
    uint8_t Read;
    for (uint8_t i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);
        Read=MyI2C_R_SDA();
        // Byte+=Read<<(7-i);
        Byte|=Read<<(7-i);          //使用或运算更好,避免重复读入
        MyI2C_W_SCL(0);
    }
    return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
    MyI2C_W_SCL(0);
    MyI2C_W_SDA(AckBit); 
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
    MyI2C_W_SCL(0);  // ✅ 明确保证从低电平开始，与老师说的原则一致
    uint8_t AckBit;    
    MyI2C_W_SDA(1);//主机释放SDA
    MyI2C_W_SCL(1);//拉高SCL

    AckBit=MyI2C_R_SDA();//读取SDA
    MyI2C_W_SCL(0);//拉低SCL
    return AckBit; 
}

void MyI2C_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);  
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);  
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
    Delay_us(10);
    return BitValue;
}

