#include "Atmel/REGX52.H"
#include "Nixie.h"
#include "Timer0.h"
#include "Key.h"

sbit LED = P2^0;

char counter = 0;
unsigned char t0_count0;
char compare;
unsigned char key_num = 0;

void main()
{
    Timer0_Init();
    compare = 40;
    while (1)
    {
        key_num = Key();
        switch (key_num)
        {
        case Key_one:
            compare+=20;
            compare %= 100;
            break;
        case Key_two:
            compare -= 20;
            compare = compare < 0 ? 0 : compare;
            break;
        }
    }
    
}

void Timer0_Routine() interrupt TF0_VECTOR
{
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
    counter++;
    counter %= 100;
    if(counter < compare)
    {
        LED = 0;
    }
    else
    {
        LED = 1;
    }
}