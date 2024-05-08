/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/26
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#include "debug.h"
#include "oled.h"
#include "kun.h"
#include "adc.h"
#include "rx5808.h"

/* Global define */

/* Global Variable */
extern uint16_t rssi[2];
extern uint16_t rssi_lpf[2];

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    ADC1_Init();
    DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)rssi, 2);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_4Cycles);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_4Cycles);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    OLED_Init();
    OLED_Clear(0);
    KUN_1();
    Delay_Ms(500);
    OLED_Clear(0);
    RX5808_Init();

    while(1)
    {
        RX5808_OLED_Update();
//        printf("%d,%d\r\n", rssi_lpf[0], rssi_lpf[1]);
//        Delay_Ms(2);
    }
}
