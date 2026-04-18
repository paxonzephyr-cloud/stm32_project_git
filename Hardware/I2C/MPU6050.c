#include "MPU6050.h"
#include "MyI2C.h"

#define MPU6050_Address 0xD0

void MPU6050_Init(void)
{
    MyI2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);//唤醒从机---可以写入
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);//2-不循环,6-每个轴不待机
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);//10分频
    MPU6050_WriteReg(MPU6050_CONFIG,0x06);//-2,3-外部同步(不需要),3-滤波(设置为110)

    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);//3-自检,2-量程选择(11-最大),-3无关位
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);//3-自检,2-量程选择(11-最大),3-高通滤波器
}

void MPU6050_GetDatad(int16_t* AccX,int16_t* AccY,int16_t* AccZ,
                        int16_t* GyroX,int16_t* GyroY,int16_t* GyroZ)
{
    uint16_t DataH,DataL;
    DataH=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *AccX=(DataH<<8)|DataL;//这是一个用补码表示的有符号数,可以直接给指针
    
    DataH=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *AccY=(DataH<<8)|DataL;

    DataH=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *AccZ=(DataH<<8)|DataL;

    DataH=MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *GyroX=(DataH<<8)|DataL;

    DataH=MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GyroY=(DataH<<8)|DataL;    
    
    DataH=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL=MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *GyroZ=(DataH<<8)|DataL;

    //还可以通过指针自增,一次性读取所有寄存器的值
}

uint8_t MPU6050_GetID(void)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);

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
