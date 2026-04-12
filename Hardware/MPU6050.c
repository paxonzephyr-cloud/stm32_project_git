#include "MPU6050.h"
#include "MyI2C.h"

#define MPU6050_Address 0xD0

void MPU6050_Init(void)
{
    MyI2C_Init();

}

//使用基本时序拼接指定地址写入时序
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_Address|0x00);//发送从机地址,进行写操作
    MyI2C_ReceiveAck();//暂时不做处理    
    MyI2C_SendByte(RegAddress);//指定寄存器进行操作
    MyI2C_ReceiveAck();
   //多个字节for循环
    MyI2C_SendByte(Data);//写入的数据内容
    MyI2C_ReceiveAck();

    MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;

    //先使用读操作进行地址定位
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_Address|0x00);//发送从机地址,进行读操作
    MyI2C_ReceiveAck();//暂时不做处理    
    MyI2C_SendByte(RegAddress);//指定寄存器进行操作
    MyI2C_ReceiveAck();

    //使用读操作进行读取
    MyI2C_Start();//SR
    MyI2C_SendByte(MPU6050_Address|0x01);//发送从机地址,进行写操作
    MyI2C_ReceiveAck();
    //多个读取用for
    Data=MyI2C_ReceiveByte();
    MyI2C_SendAck(1);           //1结束应答 
    MyI2C_Stop();
    
    return Data;
}
