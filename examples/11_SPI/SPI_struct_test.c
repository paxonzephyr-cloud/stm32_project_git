#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "W25Q64_struct.h"

uint8_t MID;
uint16_t DID;
uint8_t ArrayWrite[]={0x99,0x88,0x77,0x88};
uint8_t ArrayRead[4];

int main(void)
{
    OLED_Init();
    SoftSPI_Config spi_cfg = {
        .ss   = { GPIOA, GPIO_Pin_4 },
        .sck  = { GPIOA, GPIO_Pin_5 },
        .mosi = { GPIOA, GPIO_Pin_7 },
        .miso = { GPIOA, GPIO_Pin_6 },
    };
    W25Q64_Init(&spi_cfg);

    OLED_ShowString(1,1,"MID:   DID:");
    OLED_ShowString(2,1,"W:");
    OLED_ShowString(3,1,"R:");

    W25Q64_ReadID(&MID,&DID);
    OLED_ShowHexNum(1,5,MID,2);
    OLED_ShowHexNum(1,12,DID,4);
        
    W25Q64_SectorErase(0x000000);//按页起始地址擦除,语义更清晰
    W25Q64_PageProgram(0x000000,ArrayWrite,4);

    W25Q64_ReadData(0x000000 ,ArrayRead,4);

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
