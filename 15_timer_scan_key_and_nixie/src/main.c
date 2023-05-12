#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "Nixie.h"
#include "LCD1602.h"

void Timer0_Routine() interrupt TF0_VECTOR
{
    static unsigned int t0_count = 0;
    TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    t0_count++;
    if (t0_count >= 20)
    {
        t0_count = 0;
        Key_Loop();
    }
}

void main()
{
    unsigned char key_num = 0;
    unsigned char temp = 0;
    LCD_Init();
    Timer0_Init();
    while(1)
    {
        key_num = Key();
        if (key_num) temp = key_num;
        Nixie(1, temp);
    }
}

