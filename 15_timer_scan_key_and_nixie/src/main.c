#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"
#include "Timer0.h"
#include "Nixie.h"
#include "LCD1602.h"

static unsigned char minisec = 0;
static unsigned char sec = 0;
static unsigned char min = 0;
static unsigned char run_flag = 0;

void Sec_Loop()
{
    if (run_flag)
    {
        minisec++;
        if (minisec > 99)
        {
            minisec = 0;
            sec++;
            if (sec > 59)
            {
                sec = 0;
                min++;
                if (min > 59)
                {
                    min = 0;
                }
            }
        }
    }
}

void Timer0_Routine() interrupt TF0_VECTOR
{
    static unsigned int t0_count0 = 0;
    static unsigned int t0_count1 = 0;
    static unsigned int t0_count2 = 0;
    TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    t0_count0++;
    t0_count1++;
    t0_count2++;
    if (t0_count0 >= 20)
    {
        t0_count0 = 0;
        Key_Loop();
    }
    if (t0_count1 >= 2)
    {
        t0_count1 = 0;
        Nixie_Loop();
    }
    if (t0_count2 >= 10)
    {
        t0_count2 = 0;
        Sec_Loop();
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
        switch (key_num)
        {
        case Key_one:
            run_flag = !run_flag;
            break;
        case Key_two:
            min = 0;
            sec = 0;
            minisec = 0;
            break;
        case Key_three:
            AT24C02_WriteByte(0, min);
            AT24C02_WriteByte(1, sec);
            AT24C02_WriteByte(2, minisec);
            break;
        case Key_four:
            min = AT24C02_ReadByte(0);
            sec = AT24C02_ReadByte(1);
            minisec = AT24C02_ReadByte(2);
            break;
        default:
            break;
        }

        Nixie_SetBuf(1, min / 10);
        Nixie_SetBuf(2, min % 10);
        Nixie_SetBuf(3, 11);
        Nixie_SetBuf(4, sec / 10);
        Nixie_SetBuf(5, sec % 10);
        Nixie_SetBuf(6, 11);
        Nixie_SetBuf(7, minisec / 10);
        Nixie_SetBuf(8, minisec % 10);
    }
}

