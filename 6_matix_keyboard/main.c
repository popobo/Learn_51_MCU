#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "matrix.h"

void main()
{
	LCD_Init();
	LCD_ShowString(1, 1, "HelloWorld");
	while(1)
	{
		unsigned char key_number = MatrixKey();
		if (!key_number)
			continue;
		LCD_ShowNum(2, 1, key_number, 2);
	}
}