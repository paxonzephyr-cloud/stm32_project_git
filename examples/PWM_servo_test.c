#include "Delay.h"
#include "Key.h"
#include "OLED.h"
#include "PWM_servo.h"
#include "stm32f10x.h" // Device header

uint16_t Key;
float Angle;

int main(void)
{
    OLED_Init();
    KEY_Init(GPIO_Pin_1 | GPIO_Pin_11);
    PWM_Init();

    Angle = 90;
    Servo_SetAngle(Angle);

    while (1)
    {
        Key = KEY_GetNum(GPIO_Pin_1 | GPIO_Pin_11);

        if (Key == GPIO_Pin_1)
        {
            Angle += 30;
            if (Angle > 180)
            {
                Angle = 180;
            }
        }

        if (Key == GPIO_Pin_11)
        {
            if (Angle >= 30)
            {
                Angle -= 30;
            }
            else
            {
                Angle = 0;
            }
        }

        Servo_SetAngle(Angle);
        OLED_ShowNum(2, 1, (uint16_t)Angle, 3);
    }
}
