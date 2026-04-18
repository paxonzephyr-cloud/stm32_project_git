#include "Delay.h"
#include "OLED.h"
#include "stm32f10x.h" // Device header
#include "PWM_motor.h"
#include "Key.h"

int8_t Speed;
int main(void)
{
    OLED_Init();
    Motor_Init();
    KEY_Init(GPIO_Pin_1);

    while (1){
        if(GPIO_Pin_1==KEY_GetNum(GPIO_Pin_1)){
            Speed+=20;
            if (Speed>100)
                Speed=-100;
        }
        Motor_SetSpeed(Speed);
        OLED_ShowSignedNum(1,7,Speed,3);
    }
}
