#ifndef _RX5808_H
#define _RX5808_H

#include "ch32x035.h"

void RX5808_OLED_Update(void);
void RX5808_OLED_Init(void);
void RX5808_Init(void);
void Video_Channel_Switch(uint8_t n);
void RX5808_GPIO_Init(void);

#endif
