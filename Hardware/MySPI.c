#include "MySPI.h"

void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //PA6输入,上拉
    //PA4--CS(SS片选),PA5--CLK(SCK时钟),PA7--DI输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /*设置默认电平*/
    MySPI_W_SS(HIGH);//SS控制线默认高电平
    MySPI_W_SCK(LOW);//模式0:低电平
    //MOSI没有规定
}

void MySPI_Start(void)
{
    MySPI_W_SS(LOW);
}

void MySPI_Stop(void)
{
    MySPI_W_SS(HIGH);
}

//模式0:SS下降后,移入数据,上升沿
//      移出数据,下降沿
uint8_t MySPI_Swap(uint8_t ByteSend)
{
    MySPI_W_SCK(LOW);
    uint8_t ByteRecive=0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        //主机写入数据  //从机同样写入(这里同样没有)
        MySPI_W_MOSI(ByteSend&(0x80>>i));

        //上升沿期间主机和从机进行读取
        MySPI_W_SCK(HIGH);
        //主机读取  //从机自动读取(这里没有软件实现)
        if(MySPI_R_MISO()==1){ByteRecive|=(0x80>>i);}
        
        //置SCK为下降沿,准备下一次读取
        MySPI_W_SCK(LOW);
    }
    // MySPI_W_SCK(LOW);
    return ByteRecive;
}

uint8_t MySPI_Swap_MoveREG(uint8_t ByteSend)
{
    MySPI_W_SCK(LOW);

    for (uint8_t i = 0; i < 8; i++)
    {
        //主机写入数据  //从机同样写入(这里同样没有)
        MySPI_W_MOSI(ByteSend & 0x80);
        ByteSend=ByteSend<<1;//移位后最低位自动补零,次高位变为最高位

        //上升沿期间主机和从机进行读取
        MySPI_W_SCK(HIGH);
        //主机读取  //从机自动读取(这里没有软件实现)
        if(MySPI_R_MISO()==1){ByteSend|=0x01;}
        
        //置SCK为下降沿,准备下一次读取
        MySPI_W_SCK(LOW);
    }
    return ByteSend;
}

//模式1:上升沿移出数据,下降沿移入数据
uint8_t MySPI_Swap_1(uint8_t ByteSend)
{
    MySPI_W_SCK(LOW);
    uint8_t ByteRecive=0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        MySPI_W_SCK(HIGH);
        MySPI_W_MOSI(ByteSend&(0x80>>i));
        MySPI_W_SCK(LOW);
        if(MySPI_R_MISO()==1){ByteRecive|=(0x80>>i);}
    }
    return ByteRecive;
}
//模式3:上升沿移出数据,下降沿移入数据
//      翻转模式1的SCK
uint8_t MySPI_Swap_3(uint8_t ByteSend)
{
    // MySPI_W_SCK(LOW);
    uint8_t ByteRecive=0x00;

    for (uint8_t i = 0; i < 8; i++)
    {
        MySPI_W_SCK(LOW);
        MySPI_W_MOSI(ByteSend&(0x80>>i));
        MySPI_W_SCK(HIGH);
        if(MySPI_R_MISO()==1){ByteRecive|=(0x80>>i);}
    }
    return ByteRecive;
}
//模式2:上升沿移出数据,下降沿移入数据
//      翻转模式0的SCK
uint8_t MySPI_Swap_2(uint8_t ByteSend)
{
    // MySPI_W_SCK(LOW);
    uint8_t ByteRecive=0x00;
    for (uint8_t i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(ByteSend&(0x80>>i));
        MySPI_W_SCK(LOW);
        if(MySPI_R_MISO()==1){ByteRecive|=(0x80>>i);}
        MySPI_W_SCK(HIGH);
    }
    return ByteRecive;
}

void MySPI_W_SS(state BitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)BitValue);
}

void MySPI_W_SCK(state BitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue);
}

void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue);
}

uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}