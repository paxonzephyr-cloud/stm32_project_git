#include "W25Q64_struct.h"

void W25Q64_Init(const SoftSPI_Config *cfg)
{
    MySPI_Init(cfg);//相较于之前唯一改变的地方
}

//读取设备ID
//开始,发送指令,读高8位,读低8位,结束
void W25Q64_ReadID(uint8_t* MID,uint16_t* DID)
{
    MySPI_Start();
    MySPI_Swap(W25Q64_JEDEC_ID);//发送指令，开启通信

    *MID=MySPI_Swap(W25Q64_DUMMY_BYTE);
    *DID=MySPI_Swap(W25Q64_DUMMY_BYTE);//因为时序，不同时间调用读取函数返回结果是不一样的
    *DID=*DID<<8;
    *DID|=MySPI_Swap(W25Q64_DUMMY_BYTE);

    MySPI_Stop();
}   

//写使能
//开启,发送指令,结束
void W25Q64_WriteEnable(void)
{
    MySPI_Start();
    MySPI_Swap(W25Q64_WRITE_ENABLE);
    MySPI_Stop();
}

//等待BUSY位置0
//开启,发送指令,接收状态寄存器(时序不停,会一直接收到最新的状态寄存器),结束
void W25Q64_WaitBusy(void)
{
    int32_t timeout=100000;
    MySPI_Start();
    MySPI_Swap(W25Q64_READ_STATUS_REGISTER_1);
    //使用swap接收状态寄存器值，&0x01就是取最低位（BUSY），检查是否为零，是则进入下一步  
    while((MySPI_Swap(W25Q64_DUMMY_BYTE) & 0x01) == 0x01){
        timeout--;
        if (timeout<0) break;
    }
    MySPI_Stop();
}

//页编程
//开始,发送指令,发送地址(24位3字节),发送数据(最多256个字节)
void W25Q64_PageProgram(uint32_t Address,uint8_t* DataArray,uint16_t Count)
{
    W25Q64_WriteEnable();//写入操作之前都要写使能,
                        //之后的整条时序都有效,最后自动失能

    MySPI_Start();
    MySPI_Swap(W25Q64_PAGE_PROGRAM);
    MySPI_Swap(Address>>16);
    MySPI_Swap(Address>>8);//高位自动舍弃
    MySPI_Swap(Address);

    for (uint16_t i = 0; i < Count; i++)
    {
        MySPI_Swap(DataArray[i]);
    }   
    MySPI_Stop();

    W25Q64_WaitBusy();//等待BUSY位置0
}

//擦除(扇区擦除)
//开始,发送指令,发送地址,结束
void W25Q64_SectorErase(uint32_t Address)
{
    W25Q64_WriteEnable();

    MySPI_Start();
    MySPI_Swap(W25Q64_SECTOR_ERASE_4KB);
    MySPI_Swap(Address>>16);
    MySPI_Swap(Address>>8);//高位自动舍弃
    MySPI_Swap(Address);
    MySPI_Stop();

    W25Q64_WaitBusy();//等待BUSY位置0
}

//读取数据
//开始,发送指令,发送地址,接收数据(可多次读取,且没有页(256字节)限制),结束
void W25Q64_ReadData(uint32_t Address,uint8_t* DataArray,uint32_t Count)
{
    MySPI_Start();
    MySPI_Swap(W25Q64_READ_DATA);
    MySPI_Swap(Address>>16);
    MySPI_Swap(Address>>8);//高位自动舍弃
    MySPI_Swap(Address);

    for (uint32_t i = 0; i < Count; i++)
    {
        DataArray[i]=MySPI_Swap(W25Q64_DUMMY_BYTE);
    }
    MySPI_Stop();
}
