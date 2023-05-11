#include "Atmel/REGX52.H"
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"

enum
{
    count_mode,
    edit_mode
};

static unsigned char key_num = 0;
static unsigned char mode = count_mode;
static unsigned char time_select = DS1302_year;
static unsigned char flick_flag = 0;

void limit(char max, char min, char* target)
{
    if (*target < min) { *target = max; }
    else if (*target > max) { *target = min; }
}

void Show_Each_time(unsigned char row, unsigned char col, unsigned char which_time)
{
    if (time_select == which_time && flick_flag == 1) { LCD_ShowString(row, col, "  "); }
    else { LCD_ShowNum(row, col, DS1302_Time[which_time], 2); }
}

void Show_Time()
{
    Show_Each_time(1, 1, DS1302_year);
    Show_Each_time(1, 4, DS1302_month);
    Show_Each_time(1, 7, DS1302_date);
    Show_Each_time(2, 1, DS1302_hour);
    Show_Each_time(2, 4, DS1302_minute);
    Show_Each_time(2, 7, DS1302_second);
} 

void Count_Time()
{
    flick_flag = 0;
    DS1302_GetTime();
    Show_Time();
}

void limit_time()
{
    limit(99, 0, &DS1302_Time[DS1302_year]);
    limit(12, 1, &DS1302_Time[DS1302_month]);
    if (DS1302_Time[DS1302_month] == 1 ||
        DS1302_Time[DS1302_month] == 3 ||
        DS1302_Time[DS1302_month] == 5 ||
        DS1302_Time[DS1302_month] == 7 ||
        DS1302_Time[DS1302_month] == 8 ||
        DS1302_Time[DS1302_month] == 10 ||
        DS1302_Time[DS1302_month] == 12)
    {
        limit(31, 1, &DS1302_Time[DS1302_date]);
    }
    else if (DS1302_Time[DS1302_month] == 2)
    {
        if (DS1302_Time[DS1302_year] % 4 == 0)
        {
            limit(29, 1, &DS1302_Time[DS1302_date]);
        }
        else
        {
            limit(28, 1, &DS1302_Time[DS1302_date]);
        }
    }
    else
    {
        limit(30, 1, &DS1302_Time[DS1302_date]);
    }
    limit(23, 0, &DS1302_Time[DS1302_hour]);
    limit(59, 0, &DS1302_Time[DS1302_minute]);
    limit(59, 0, &DS1302_Time[DS1302_second]);
}

void Edit_Time()
{   
    switch (key_num)
    {
    case Key_two:
        time_select++;
        if (time_select == DS1302_second + 1) { time_select = DS1302_year; }
        break;
    case Key_three:
        DS1302_Time[time_select]++;
        limit_time();
        Show_Time();
        break;
    case Key_four:
        DS1302_Time[time_select]--;
        limit_time();
        break;
    }
    Show_Time();
}

void main()
{
    unsigned char sec = 0;
	LCD_Init();
    LCD_ShowString(1, 1, "  -  -  ");
    LCD_ShowString(2, 1, "  :  :  ");
    DS1302_Init();
    DS1302_SetTime();
    Timer0_Init();
    while(1)
	{
        key_num = Key();
        if (key_num == Key_one)
        {
            if(mode == count_mode) { mode = edit_mode; }
            else if(mode == edit_mode) {
                mode = count_mode;
                DS1302_SetTime();
            }
        }
        
        switch (mode)
        {
        case count_mode:
            Count_Time();
            break;
        case edit_mode:
            Edit_Time();
            break;
        }
	}
}

void Timer0_Routine() interrupt 1
{
    static unsigned int t0_count = 0;
    TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
    t0_count++;
    if (t0_count >= 1000)
    {
        t0_count = 0;
        if (mode == edit_mode)
            flick_flag = !flick_flag;
    }
}