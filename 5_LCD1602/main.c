#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	
	char a = 0;
	
	LCD_Init();
	LCD_ShowChar(1, 1, 'A');
	LCD_ShowString(1, 3, "Hello");
	LCD_ShowNum(2, 1, 666, 3);
	LCD_ShowSignedNum(2, 5, -222, 3);
	LCD_ShowHexNum(2, 9, 0xAA, 2);
	LCD_ShowBinNum(1, 8, 0xBB, 8);
	
	while(1)
	{
		LCD_ShowNum(1, 3, a, 3);
		Delay_ms(500);
		a++;
	}
}