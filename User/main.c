#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
    led_in red={GPIOB,GPIO_Pin_1,1};
	LED_Init(&red);

	/*OLED显示*/
	OLED_ShowChar(1, 1, 'D');				//1行1列显示字符A
	
	OLED_ShowString(1, 3, "Hello-World!");	//1行3列显示字符串HelloWorld!
	

	while (1)
	{
		Delay_ms(500);
        LED_ON(&red);
		Delay_ms(500);
        LED_OFF(&red);
    }
}
