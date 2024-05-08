#ifndef __OLED_H
#define __OLED_H

//--------------OLED��������---------------------
#define PAGE_SIZE    8
#define XLevelL		0x00
#define XLevelH		0x10
#define YLevel       0xB0
#define	Brightness	 0xFF
#define WIDTH 	     128
#define HEIGHT 	     64	

//-------------д��������ݶ���-------------------
#define OLED_CMD     0	//д����
#define OLED_DATA    1	//д����

//-----------------OLED�˿ڶ���----------------
#define OLED_DC   GPIO_Pin_3     //����/��������ź�
#define OLED_RST  GPIO_Pin_2    //��λ�ź�

//-----------------OLED�˿ڲ�������----------------
#define OLED_DC_Clr()  GPIO_ResetBits(GPIOA,OLED_DC)
#define OLED_DC_Set()  GPIO_SetBits(GPIOA,OLED_DC)

#define OLED_RST_Clr()  GPIO_ResetBits(GPIOA,OLED_RST)
#define OLED_RST_Set()  GPIO_SetBits(GPIOA,OLED_RST)


//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Reset(void);
void OLED_Init_GPIO(void);
void OLED_Init(void);
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);
void OLED_Display(void);
void OLED_Clear(unsigned dat);

#endif
