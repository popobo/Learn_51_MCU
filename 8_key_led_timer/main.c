#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "matrix.h"
#include "timer0.h"
#include "INTRINS.h"
#include "Key.h"

/*
void Timer0_Init()
{
	// TMOD = 0x01; // 0000 0001 不可位寻址
	TMOD = TMOD & 0xF0;
	TMOD = TMOD | 0x0;
	TF0 = 0;
	TR0 = 1;
	TH0 = 64535 / 256;
	TL0 = 64535 % 256 + 1 ;
	
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}
*/

static unsigned char led_mode = 0;

void main()
{
	unsigned char key_num = 0;
	P2 = 0xFE;
	Timer0_Init();
	while(1)
	{
		key_num = Key();
		if(key_num == 1)
		{
			led_mode++;
			led_mode %= 2;
		}
	}
}



void Timer0_Routine() interrupt 1
{
	static unsigned int t0_count = 0;
	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	t0_count++;
	if(t0_count >= 500)
	{
		t0_count = 0;
		if(led_mode == 0)
			P2 = _crol_(P2, 1);
		if(led_mode == 1)
			P2 = _cror_(P2, 1);
	}
}