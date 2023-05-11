#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "matrix.h"
#include "timer0.h"
#include "INTRINS.h"
#include "Key.h"


static unsigned char led_mode = 0;

static unsigned char sec = 59;
static unsigned char min = 59;
static unsigned char hour = 23;

void main()
{
	LCD_Init();
	Timer0_Init();
	LCD_ShowString(1, 1, "Clock:");
	LCD_ShowString(2, 1, "  :  :  ");
	while(1)
	{
		LCD_ShowNum(2, 1, hour, 2);
		LCD_ShowNum(2, 4, min, 2);
		LCD_ShowNum(2, 7, sec, 2);
	}
}



void Timer0_Routine() interrupt 1
{
	static unsigned int t0_count = 0;
	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	t0_count++;
	if(t0_count >= 1000)
	{
		t0_count = 0;
		++sec;
		if(sec >= 60)
		{
			sec = 0;
			++min;
			if(min >= 60)
			{
				min = 0;
				++hour;
				if(hour >= 24)
				{
					hour = 0;
				}
			}
		}
	}
}