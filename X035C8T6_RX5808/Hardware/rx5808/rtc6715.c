#include "rtc6715.h"
#include "ch32x035.h"
#include "debug.h"

void RTC6715_Init(void)
{
    RTC6715_SPI_Init();
    Delay_Ms(1);
    RTC6715_Register_A_Init();
    RTC6715_Power_Down_Control_Register_Init();
}

void RTC6715_Power_Down_Control_Register_Init(void)
{
//    u32 sRegPDC = 0x10DF3;      //video only
    uint32_t sRegPDC = 0x10C13;      //video + audio
    uint8_t i;

    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
    RTC6715_SPI_Select(ENABLE);

    // Address (0x0A)
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(1);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(1);

    // Read/Write (Write)
    RTC6715_SPI_Send(1);

    // Data (20 LSB bits)
    for (i = 0; i < 20; i++) {
        ((sRegPDC>>i) & 0x1) ? RTC6715_SPI_Send(1) : RTC6715_SPI_Send(0);
    }

    // Disable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
}

void RTC6715_Register_A_Init(void)
{
    uint32_t sRegA = 0x00008;
    uint8_t i;

    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
    RTC6715_SPI_Select(ENABLE);

    // Address (0x00)
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);

    // Read/Write (Write)
    RTC6715_SPI_Send(1);

    // Data (20 LSB bits)
    for (i = 0; i < 20; i++) {
        ((sRegA>>i) & 0x1) ? RTC6715_SPI_Send(1) : RTC6715_SPI_Send(0);
    }

    // Disable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
}

void RTC6715_SPI_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure_SPI2 = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure_SPI2.GPIO_Pin = GPIO_Pin_8;   //NSS
    GPIO_InitStructure_SPI2.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_SPI2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_SPI2);
    GPIO_SetBits(GPIOB, GPIO_Pin_8);

    GPIO_InitStructure_SPI2.GPIO_Pin = GPIO_Pin_10;   //SCK
    GPIO_InitStructure_SPI2.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_SPI2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_SPI2);
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);

    GPIO_InitStructure_SPI2.GPIO_Pin = GPIO_Pin_9;   //MOSI
    GPIO_InitStructure_SPI2.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_SPI2.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_SPI2);
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

void RTC6715_SPI_Send(uint8_t n)
{
    GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
    if(n == 1)
    {
        GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_MOSI);
    }
    else {
        GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_MOSI);
    }
    Delay_Us(1);
    GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
    GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_SCK);
    Delay_Us(1);
}

void RTC6715_SPI_Select(FunctionalState NewState)
{
    Delay_Us(1);
    if(NewState != DISABLE)
    {
        GPIO_ResetBits(SPI_Soft_GPIO_Port, SPI_Soft_CS);
    }
    else
    {
        GPIO_SetBits(SPI_Soft_GPIO_Port, SPI_Soft_CS);
    }
    Delay_Us(1);
}

uint32_t RTC6715_CalculateFrequencyData(u16 frequency)
{
    uint16_t N;
    uint8_t A;
    frequency = (frequency - 479)/2;
    N = frequency/32;
    A = frequency%32;
    return (N << 7 | A);
}

void RTC6715_SetFrequency(u16 frequency)
{
    uint32_t sRegB;
    uint8_t i;

    sRegB = RTC6715_CalculateFrequencyData(frequency);

    // Enable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
    RTC6715_SPI_Select(ENABLE);

    // Address (0x01)
    RTC6715_SPI_Send(1);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);
    RTC6715_SPI_Send(0);

    // Read/Write (Write)
    RTC6715_SPI_Send(1);

    // Data (20 LSB bits)
    for (i = 0; i < 20; i++) {
        ((sRegB>>i) & 0x1) ? RTC6715_SPI_Send(1) : RTC6715_SPI_Send(0);
    }

    // Disable SPI pin
    RTC6715_SPI_Select(DISABLE);
    Delay_Us(1);
}
