#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "MPU6050.h"

int main(void)
{
    OLED_Init();
    MPU6050_Init();

    MPU6050_WriteReg(0x6B,0x00);//解除睡眠模式
    MPU6050_WriteReg(0x19,0x66);


    uint8_t Psc=MPU6050_ReadReg(0x19);//写入预分频
    OLED_ShowHexNum(1,1,Psc,4);
    
    uint8_t ID=MPU6050_ReadReg(0x75);//读取硬件ID号----6500<-->70
    OLED_ShowHexNum(2,1,ID,4);

    while (1)
    {
    }
}
