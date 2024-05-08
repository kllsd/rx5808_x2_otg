#ifndef _RTC6715_H
#define _RTC6715_H

#include "ch32x035.h"

#define SPI_Soft_GPIO_Port  GPIOB
#define SPI_Soft_CS     GPIO_Pin_8
#define SPI_Soft_SCK     GPIO_Pin_10
#define SPI_Soft_MOSI    GPIO_Pin_9

void RTC6715_Init(void);
void RTC6715_Power_Down_Control_Register_Init(void);
void RTC6715_Register_A_Init(void);
void RTC6715_SPI_Init(void);
void RTC6715_SPI_Send(uint8_t n);
void RTC6715_SPI_Select(FunctionalState NewState);
uint32_t RTC6715_CalculateFrequencyData(uint16_t frequency);
void RTC6715_SetFrequency(u16 frequency);

#endif
