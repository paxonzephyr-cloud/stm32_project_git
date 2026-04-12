#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f10x.h"
#include "MPU6050.h"
#include "MyI2C.h"

#define MPU6050_Address         0xD0        //从机地址


void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAddress);

#endif
