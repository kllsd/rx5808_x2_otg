#include "ch32x035.h"
#include "spi.h"

void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure_SPI1 = {0};
    SPI_InitTypeDef SPI_InitStructure_SPI1 = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitStructure_SPI1.GPIO_Pin = GPIO_Pin_4;   //SPI1_NSS
    GPIO_InitStructure_SPI1.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_SPI1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure_SPI1);
    GPIO_SetBits(GPIOA, GPIO_Pin_4);

    GPIO_InitStructure_SPI1.GPIO_Pin = GPIO_Pin_5;   //SPI1_SCK
    GPIO_InitStructure_SPI1.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure_SPI1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure_SPI1);

//    GPIO_InitStructure_SPI1.GPIO_Pin = GPIO_Pin_6;   //SPI1_MISO
//    GPIO_InitStructure_SPI1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure_SPI1);

    GPIO_InitStructure_SPI1.GPIO_Pin = GPIO_Pin_7;   //SPI1_MOSI
    GPIO_InitStructure_SPI1.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure_SPI1.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure_SPI1);

    SPI_I2S_DeInit(SPI1);
    SPI_InitStructure_SPI1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure_SPI1.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure_SPI1.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure_SPI1.SPI_CRCPolynomial = 7;
    SPI_InitStructure_SPI1.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure_SPI1.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure_SPI1.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure_SPI1.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure_SPI1.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI1, &SPI_InitStructure_SPI1);
//    SPI_SSOutputCmd(SPI1, ENABLE);
//    SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
    SPI_Cmd(SPI1, ENABLE);
}
