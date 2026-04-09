#include "Delay.h"
#include "OLED.h"
#include "stdio.h"
#include "stm32f10x.h" // Device header
#include "USART_Packet_text.h"

int main(void)
{
    OLED_Init();
    Serial_Packet_text_Init();

    OLED_ShowString(1, 1, "TxPacket");
    OLED_ShowString(3, 1, "RxPacket");

    while (1){
        if(Serial_GetRXFlag()==1){
            OLED_ShowString(4,1,"                ");
            OLED_ShowString(4,1,Serial_RxPacket);

        }

    }
}
