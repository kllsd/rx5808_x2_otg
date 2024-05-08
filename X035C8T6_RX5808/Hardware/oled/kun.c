#include "ch32x035.h"
#include "oled.h"
#include "string.h"
#include "kun.h"
#include "debug.h"
#include "bmp_kun.h"
#include "gui.h"

void KUN_1(void)
{
	GUI_DrawBMP(0,0,128,64, BMP_kun, 1);
}

void KUN_2(void)
{
	GUI_DrawBMP(0,0,128,64, BMP_kun, 0);
}

void KUN_WD(void)
{
	uint8_t t = 75;
	GUI_DrawBMP(0,0,128,64, fps1, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps2, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps3, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps4, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps5, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps6, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps7, 0);
	Delay_Ms(t);
	GUI_DrawBMP(0,0,128,64, fps8, 0);
	Delay_Ms(t);
}
