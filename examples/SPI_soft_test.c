#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;
uint8_t ArrayWrite[]={0x55,0x66,0x77,0x88};
uint8_t ArrayRead[4];


int main(void)
{
    OLED_Init();
    W25Q64_Init();

    OLED_ShowString(1,1,"MID:   DID:");
    OLED_ShowString(2,1,"W:");
    OLED_ShowString(3,1,"R:");

    W25Q64_ReadID(&MID,&DID);
    OLED_ShowHexNum(1,5,MID,2);
    OLED_ShowHexNum(1,12,DID,4);
        
    //注释掉这两行已验证掉电丢失
    //只擦除不写入验证擦除后全为FF
    //不擦出只写入验证只能1写0,不能0写1---0xAA,0xBB,0xCC,0xDD----A0,B2,C0,D4-----收上一次写入数据影响,每次结果可能不一样
     //                            --0x55,0x66,0x77,0x88----00.22,40,80   -结果就是写入的数据&原始数据               
    W25Q64_SectorErase(0x000000);//按页起始地址擦除,语义更清晰
    W25Q64_PageProgram(0x0000FF,ArrayWrite,4);

    W25Q64_ReadData(0x0000FF ,ArrayRead,4);//读取可跨页,写入不能
    // W25Q64_ReadData(0x000000 ,ArrayRead,4);

    OLED_ShowHexNum(2,3,ArrayWrite[0],2);
    OLED_ShowHexNum(2,6,ArrayWrite[1],2);
    OLED_ShowHexNum(2,9,ArrayWrite[2],2);
    OLED_ShowHexNum(2,12,ArrayWrite[3],2);

    OLED_ShowHexNum(3,3,ArrayRead[0],2);
    OLED_ShowHexNum(3,6,ArrayRead[1],2);
    OLED_ShowHexNum(3,9,ArrayRead[2],2);
    OLED_ShowHexNum(3,12,ArrayRead[3],2);
    while (1)
    {

    }
}
