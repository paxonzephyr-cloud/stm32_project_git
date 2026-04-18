#include "Delay.h"
#include "stm32f10x.h" // Device header
#include "OLED.h"
#include "USART_TX_RX.h"
#include "stdio.h"

uint8_t RxData;

int main(void)
{
    OLED_Init();
    OLED_ShowString(1,1,"RxData:");

    Seria_TX_RX_Init();

    while (1){
        if(Serial_GetRXFlag()==1){
            RxData=Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1,8,RxData,2);
        }
    }
}

