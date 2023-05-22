#include "Atmel/REGX52.H"
#include "LCD1602.h"
#include "XPT2046.h"
#include "Delay.h"

unsigned int ad_value;

void main()
{

    LCD_Init();
    LCD_ShowString(1, 1, "ADD NTC RG");
    while(1)
    {
        ad_value = XPT2046_ReadAD(XPT2046_XP_8);
        LCD_ShowNum(2, 1, ad_value, 3);
        ad_value = XPT2046_ReadAD(XPT2046_YP_8);
        LCD_ShowNum(2, 5, ad_value, 3);
        ad_value = XPT2046_ReadAD(XPT2046_VBAT_8);
        LCD_ShowNum(2, 9, ad_value, 3);
        Delay_ms(10);
    }
}