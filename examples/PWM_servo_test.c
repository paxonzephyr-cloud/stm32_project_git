#include "Delay.h"
#include "OLED.h"
#include "PWM_servo.h"
#include "stm32f10x.h" // Device header
#include "Key.h"
#include "LED.h"

uint8_t Key;
float Angle;

int main(void)
{
    OLED_Init();
    KEY_Init(GPIO_Pin_1|GPIO_Pin_11);
    PWM_Init();

    while (1){
        Key=KEY_GetNum(GPIO_Pin_1);
        if (Key==GPIO_Pin_1){
            Angle+=30;
            if(Angle>0){
                Angle=0;
            }
        }
        Servo_SetAngle(Angle);
        OLED_ShowNum(1,7,Angle,3);        
    }
}
