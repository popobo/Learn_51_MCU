#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"
#include "OneWare.h"
#include "DS18B20.h"

unsigned char ack = 0;
float T;

void main()
{
    DS18B20_CovertT();
    Delay_ms(1000); //转换温度需要耗时
    LCD_Init();
    LCD_ShowString(1, 1, "Temperature:");

    while (1)
    {
        DS18B20_CovertT();
        T = DS18B20_ReadT();
        if (T < 0)
        {
            LCD_ShowChar(2, 1, '-');
            T = -T;
        }
        else
        {
            LCD_ShowChar(2, 1, '+');
        }
        LCD_ShowNum(2, 2, T, 3);
        LCD_ShowChar(2, 5, '.');
        LCD_ShowNum(2, 6, (unsigned long)(T * 10000) % 10000, 4);
    }
}