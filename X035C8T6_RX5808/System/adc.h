#ifndef __ADC_H_
#define __ADC_H_

#include "ch32x035.h"

void ADC1_Init(void);
void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);

#endif
