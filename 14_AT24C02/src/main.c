#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"
#include "AT24C02.h"

unsigned char read_byte = 0;
unsigned char key_num = 0;
unsigned int num = 11111;

void main()
{
    LCD_Init();
    LCD_ShowNum(1, 1, num, 5);
    while(1)
    {
        key_num = Key();
        switch (key_num)
        {
        case Key_one:
            num++;
            LCD_ShowNum(1, 1, num, 5);
            break;
        case Key_two:
            num--;
            LCD_ShowNum(1, 1, num, 5);
            break;
        case Key_three:
            AT24C02_WriteByte(0, num % 256);
            Delay_ms(5);
            AT24C02_WriteByte(1, num / 256);
            Delay_ms(5);
            LCD_ShowString(2, 1, "Write");
            Delay_ms(1000);
            LCD_ShowString(2, 1, "     ");
            break;
        case Key_four:
            num = AT24C02_ReadByte(1);
            num = num << 8;
            num |= AT24C02_ReadByte(0);
            LCD_ShowNum(1, 1, num, 5);
            LCD_ShowString(2, 1, "Read");
            Delay_ms(1000);
            LCD_ShowString(2, 1, "    ");
            break;
        }
    }
}