#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"
#include "OneWare.h"
#include "DS18B20.h"
#include "AT24C02.h"
#include "Timer0.h"

unsigned char ack = 0;
float T = 0;
float T_show = 0;
char t_low = 0;
char t_high = 0;
unsigned char key_num = 0;

void main()
{
    t_low = AT24C02_ReadByte(0);
    t_high = AT24C02_ReadByte(1);
    if(t_high > 125 || t_low < -55 || t_high <= t_low)
    {
        t_high = 25;
        t_low = 0;
    }

    Timer0_Init();
    LCD_Init();
    LCD_ShowString(1, 1, "T:");
    LCD_ShowString(2, 1, "TH:");
    LCD_ShowString(2, 9, "TL:");
    LCD_ShowSignedNum(2, 4, t_high, 3);
    LCD_ShowSignedNum(2, 12, t_low, 3);
    while (1)
    {
        key_num = Key();
        DS18B20_CovertT();
        T = DS18B20_ReadT();
        if (T < 0)
        {
            LCD_ShowChar(1, 3, '-');
            T_show = -T;
        }
        else
        {
            T_show = T;
            LCD_ShowChar(1, 3, '+');
        }
        LCD_ShowNum(1, 4, T_show, 3);
        LCD_ShowChar(1, 7, '.');
        LCD_ShowNum(1, 8, (unsigned long)(T_show * 100) % 100, 2);

        //阈值判断
        switch (key_num)
        {
        case Key_one:
            t_high++;
            if(t_high > 125) t_high = 125;
            
            break;
        case Key_two:
            t_high--;
            if(t_high <= t_low) t_high++;
            break;
        case Key_three:
            t_low++;
            if(t_low >= t_high) t_low--;
            break;
        case Key_four:
            t_low--;
            if(t_low < -55) t_low = -55;
            break;
        }

        if (T > t_high)
        {
            LCD_ShowString(1, 13, "OV:H");
        }
        else if (T < t_low)
        {
            LCD_ShowString(1, 13, "OV:L");
        }
        else
        {
            LCD_ShowString(1, 13, "    ");
        }

        if (key_num)
        {
            AT24C02_WriteByte(0, t_low);
            AT24C02_WriteByte(1, t_high);
            LCD_ShowSignedNum(2, 4, t_high, 3);
            LCD_ShowSignedNum(2, 12, t_low, 3);
        }
    }
}

void Timer0_Routine() interrupt TF0_VECTOR
{
    static unsigned int t0_count0 = 0;
    TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    t0_count0++;
    if (t0_count0 >= 20)
    {
        t0_count0 = 0;
        Key_Loop();
    }
}
