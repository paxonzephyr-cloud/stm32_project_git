#include "SysTick.h"

static volatile uint32_t tick_count;

void SysTick_Init(void)
{
    //  系统时钟72M---72M的时钟周期=1s-----72000个时钟周期=1ms
    SysTick_Config(SystemCoreClock/1000 );
    //函数自动完成中断配置
}

//需要将stm32F10x_it.c中的SysTick_Handler设置为__weak
void SysTick_Handler(void)
{
    tick_count++;
}

uint32_t Get_Tick(void)
{
    return tick_count;
}
