#include "stm32f10x.h" // Device header
#include "PWM_motor_Init.h"
#include "LED.h"

void Motor_Init(void)
{
    PWM_motor_Init();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_Inistructure;
    GPIO_Inistructure.GPIO_Mode = GPIO_Mode_Out_PP;  
    GPIO_Inistructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;              
    GPIO_Inistructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_Inistructure); 

    // LED_Init(GPIO_Pin_4|GPIO_Pin_5);
    // LED_ON(GPIO_Pin_4|GPIO_Pin_5);
}

void Motor_SetSpeed(int8_t Speed)
{
    if(Speed>0){
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
        PWM_SetCompare3(Speed);
    }else {
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        PWM_SetCompare3(-Speed);
    }


}

