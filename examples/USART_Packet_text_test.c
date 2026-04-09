#include "Delay.h"
#include "OLED.h"
#include "stdio.h"
#include "stm32f10x.h" // Device header
#include "USART_Packet_text.h"
#include "LED.h"
#include <string.h>

int main(void)
{
    LED_Init(GPIO_Pin_1);
    OLED_Init();
    Serial_Packet_text_Init();

    OLED_ShowString(1, 1, "TxPacket");
    OLED_ShowString(3, 1, "RxPacket");

    while (1){
        if(Serial_GetRXFlag()==1){
            OLED_ShowString(4,1,"                ");
            OLED_ShowString(4,1,Serial_RxPacket);

            if(strcmp(Serial_RxPacket,"LED_ON")==0){
                LED_ON(GPIO_Pin_1);
                Serial_SendString("LED_ON_OK\r\n");
                OLED_ShowString(2,1,"                ");
                OLED_ShowString(2,1,"LED_ON_OK");
            }else if(strcmp(Serial_RxPacket,"LED_OFF")==0){
                LED_OFF(GPIO_Pin_1);
                Serial_SendString("LED_OFF_OK\r\n");
                OLED_ShowString(2,1,"                ");
                OLED_ShowString(2,1,"LED_OFF_OK");
            }else {
                Serial_SendString("ERROR_COMMAND\r\n");
                OLED_ShowString(2,1,"                ");
                OLED_ShowString(2,1,"ERROR_COMMAND");
            }   
        }
    }
}
