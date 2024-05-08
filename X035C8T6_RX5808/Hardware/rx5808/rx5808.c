#include "rx5808.h"
#include "ch32x035.h"
#include "rtc6715.h"
#include "debug.h"
#include "gui.h"
#include "math.h"

uint16_t rssi[2] = {0};
uint16_t rssi_last[2] = {0};
uint16_t rssi_lpf[2] = {0};
uint16_t rssi_max[2] = {0};
uint8_t rssi_length[2] = {0};
float alpha = 0.05f;
int16_t rssi_err = 0;
uint8_t video_channel = 0;
uint16_t rx5808_t[2] = {0};
uint8_t rx5808_i=0, rx5808_j=0;

const uint16_t Rx5808_Freq[6][8]=
{
    {5865,5845,5825,5805,5785,5765,5745,5725},      //A CH1-8
    {5733,5752,5771,5790,5809,5828,5847,5866},      //B CH1-8
    {5705,5685,5665,5645,5885,5905,5925,5945},      //C CH1-8
    {5740,5760,5780,5800,5820,5840,5860,5880},      //D CH1-8
    {5658,5695,5732,5769,5806,5843,5880,5917},      //E CH1-8
    {5362,5399,5436,5473,5510,5547,5584,5621}       //F CH1-8
};

void RX5808_OLED_Update(void)
{
    rssi_lpf[0] = alpha * rssi[0] + (1 - alpha) * rssi_last[0];
    rssi_last[0] = rssi_lpf[0];
    rssi_lpf[1] = alpha * rssi[1] + (1 - alpha) * rssi_last[1];
    rssi_last[1] = rssi_lpf[1];

    if(rssi_lpf[0] > rssi_max[0])
    {
        rssi_max[0] = rssi_lpf[0];
    }
    if(rssi_lpf[1] > rssi_max[1])
    {
        rssi_max[1] = rssi_lpf[1];
    }

    rssi_length[0] = 101.0f*rssi_lpf[0]/rssi_max[0];
    rssi_length[1] = 101.0f*rssi_lpf[1]/rssi_max[1];

    if(rssi_length[0] > rssi_length[1])
    {
        if(rx5808_t[0] > 1000)
        {
            if(video_channel == 0)
            {

            }
            else {
                video_channel = 0;
                Video_Channel_Switch(video_channel);
            }
        }
        else {
            rx5808_t[0]++;
            rx5808_t[1] = 0;
        }
    }
    else {
        if(rx5808_t[1] > 1000)
        {
            if(video_channel == 1)
            {

            }
            else {
                video_channel = 1;
                Video_Channel_Switch(video_channel);
            }
        }
        else {
            rx5808_t[1]++;
            rx5808_t[0] = 0;
        }
    }

    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) == Bit_RESET)
    {
        Delay_Ms(20);
        if(rx5808_i == 5 && rx5808_j == 7)
        {
            rx5808_i = 0;
            rx5808_j = 0;
        }
        else {
            if(rx5808_j == 7)
            {
                rx5808_j = 0;
                rx5808_i++;
            }
            else {
                rx5808_j++;
            }
        }
        RTC6715_SetFrequency(Rx5808_Freq[rx5808_i][rx5808_j]);
        GUI_ShowChar(104, 0, 65+rx5808_i, 16, 1);
        GUI_ShowNum(112, 0, rx5808_j, 1, 16, 1);
        GUI_ShowNum(48, 17, Rx5808_Freq[rx5808_i][rx5808_j], 4, 16, 1);
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) != Bit_SET);
        Delay_Ms(20);
    }
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == Bit_RESET)
    {
        Delay_Ms(20);
        if(rx5808_i == 0 && rx5808_j == 0)
        {
            rx5808_i = 5;
            rx5808_j = 7;
        }
        else {
            if(rx5808_j == 0)
            {
                rx5808_j = 7;
                rx5808_i--;
            }
            else {
                rx5808_j--;
            }
        }
        RTC6715_SetFrequency(Rx5808_Freq[rx5808_i][rx5808_j]);
        GUI_ShowChar(104, 0, 65+rx5808_i, 16, 1);
        GUI_ShowNum(112, 0, rx5808_j, 1, 16, 1);
        GUI_ShowNum(48, 17, Rx5808_Freq[rx5808_i][rx5808_j], 4, 16, 1);
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) != Bit_SET);
        Delay_Ms(20);
    }

    GUI_Fill_not_display(2, 46, 103, 50, 0);
    GUI_Fill_not_display(2, 57, 103, 61, 0);
    GUI_Fill_not_display(2, 46, rssi_length[0], 50, 1);
    GUI_FillRectangle(2, 57, rssi_length[1], 61, 1);
}

void RX5808_OLED_Init(void)
{
    GUI_ShowString(0, 0, "VRX Channel:", 16, 1);
    GUI_ShowString(104, 0, "A0", 16, 1);
    GUI_ShowString(0, 17, "Freq:", 16, 1);
    GUI_ShowNum(48, 17, Rx5808_Freq[0][0], 4, 16, 1);
    GUI_ShowString(88, 17, "MHz", 16, 1);
    GUI_DrawRectangle(0, 44, 105, 52, 1);
    GUI_DrawRectangle(0, 55, 105, 63, 1);
    GUI_Fill_not_display(108, 44, 127, 52, 1);
    GUI_Fill_not_display(108, 55, 127, 63, 0);
    GUI_ShowString(108, 45, "CH1", 8, 0);
    GUI_ShowString(108, 56, "CH2", 8, 1);
}

void RX5808_Init(void)
{
    RTC6715_Init();
    RX5808_GPIO_Init();
    RTC6715_SetFrequency(Rx5808_Freq[0][0]);
    Delay_Ms(100);
    Video_Channel_Switch(video_channel);
    RX5808_OLED_Init();
}

void Video_Channel_Switch(uint8_t n)
{
    if(n == 1)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        GPIO_SetBits(GPIOB, GPIO_Pin_1);
        GUI_Fill_not_display(108, 44, 127, 52, 0);
        GUI_Fill_not_display(108, 55, 127, 63, 1);
        GUI_ShowString(108, 45, "CH1", 8, 1);
        GUI_ShowString(108, 56, "CH2", 8, 0);
    }
    else if(n == 0)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_1);
        GPIO_SetBits(GPIOB, GPIO_Pin_0);
        GUI_Fill_not_display(108, 44, 127, 52, 1);
        GUI_Fill_not_display(108, 55, 127, 63, 0);
        GUI_ShowString(108, 45, "CH1", 8, 0);
        GUI_ShowString(108, 56, "CH2", 8, 1);
    }
    else {
        GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
    }
}

void RX5808_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure_Video = {0};
    GPIO_InitTypeDef GPIO_InitStructure_Key = {0};
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure_Video.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure_Video.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_Video.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_Video);
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);

    GPIO_InitStructure_Key.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure_Key.GPIO_Mode = GPIO_Mode_IPU;
//    GPIO_InitStructure_Key.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure_Key);
}
