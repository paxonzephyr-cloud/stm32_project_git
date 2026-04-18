#include "MySPI_struct.h"
#include "stm32f10x.h" // Device header

static SoftSPI_Config spi; // 内部静态，外部不可见

static uint32_t get_rcc_periph(GPIO_TypeDef *gpio);
static void MySPI_W_SS(state BitValue);
static void MySPI_W_SCK(state BitValue);
static void MySPI_W_MOSI(state BitValue);
static uint8_t MySPI_R_MISO(void);

static uint32_t get_rcc_periph(GPIO_TypeDef *gpio)
{
    if      (gpio == GPIOA) return RCC_APB2Periph_GPIOA;
    else if (gpio == GPIOB) return RCC_APB2Periph_GPIOB;
    else if (gpio == GPIOC) return RCC_APB2Periph_GPIOC;
    else if (gpio == GPIOD) return RCC_APB2Periph_GPIOD;
    else                    return 0;
}

void MySPI_Init(const SoftSPI_Config *cfg)
{
    spi = *cfg; // 拷贝配置到静态实例

    RCC_APB2PeriphClockCmd(get_rcc_periph(spi.ss.gpio),   ENABLE);
    RCC_APB2PeriphClockCmd(get_rcc_periph(spi.sck.gpio),  ENABLE);
    RCC_APB2PeriphClockCmd(get_rcc_periph(spi.mosi.gpio), ENABLE);
    RCC_APB2PeriphClockCmd(get_rcc_periph(spi.miso.gpio), ENABLE);

    GPIO_InitTypeDef cfg_gpio;
    GPIO_StructInit(&cfg_gpio);
    cfg_gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    cfg_gpio.GPIO_Speed = GPIO_Speed_50MHz;

    cfg_gpio.GPIO_Pin = spi.ss.pin;   GPIO_Init(spi.ss.gpio,   &cfg_gpio);
    cfg_gpio.GPIO_Pin = spi.sck.pin;  GPIO_Init(spi.sck.gpio,  &cfg_gpio);
    cfg_gpio.GPIO_Pin = spi.mosi.pin; GPIO_Init(spi.mosi.gpio, &cfg_gpio);

    cfg_gpio.GPIO_Pin  = spi.miso.pin;
    cfg_gpio.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(spi.miso.gpio, &cfg_gpio);

    MySPI_W_SS(HIGH);
    MySPI_W_SCK(LOW);
}

void MySPI_Start(void) 
{
    MySPI_W_SS(LOW);
}

void MySPI_Stop(void)  
{
    MySPI_W_SS(HIGH);
}

uint8_t MySPI_Swap(uint8_t ByteSend)
{
    MySPI_W_SCK(LOW);
    uint8_t ByteReceive = 0x00;
    for (uint8_t i = 0; i < 8; i++)
    {
        //主机写入数据  //从机同样写入(这里同样没有)
        MySPI_W_MOSI(ByteSend&(0x80>>i)?HIGH:LOW);
        
        //上升沿期间主机和从机进行读取
        MySPI_W_SCK(HIGH);
        //主机读取  //从机自动读取(这里没有软件实现)
        if(MySPI_R_MISO()==1){ByteReceive|=(0x80>>i);}
        
        //置SCK为下降沿,准备下一次读取
        MySPI_W_SCK(LOW);
    }
    return ByteReceive;
}

static void MySPI_W_SS(state BitValue)
{
    GPIO_WriteBit(spi.ss.gpio,spi.ss.pin,(BitAction)BitValue);
}

static void MySPI_W_SCK(state BitValue)
{
    GPIO_WriteBit(spi.sck.gpio,spi.sck.pin,(BitAction)BitValue);
}

static void MySPI_W_MOSI(state BitValue)
{
    GPIO_WriteBit(spi.mosi.gpio,spi.mosi.pin,(BitAction)BitValue);
}

static uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(spi.miso.gpio,spi.miso.pin);
}