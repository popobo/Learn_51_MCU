#include "Atmel/REGX52.H"
#include "LCD1602.h"
#include "XPT2046.h"
#include "Delay.h"

unsigned int ad_value;

void main()
{

    LCD_Init();
    LCD_ShowString(1, 1, "ADD");
    while(1)
    {
        ad_value = XPT2046_ReadAD(XPT2046_XP);
        LCD_ShowNum(2, 1, ad_value, 4);
        Delay_ms(10);
    }
}