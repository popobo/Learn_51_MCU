#include "Atmel/REGX52.H"
#include "LCD1602.h"
#include "Delay.h"

/**
  * @brief 扫描获取按键矩阵按键键�?
  * @param �?
  * @retval 按键键�?
  */

unsigned char MatrixKey()
{
	unsigned char key_number = 0;
	
	P1 = 0xFF;
	P1_3 = 0;
	if (!P1_7) { Delay_ms(20); while(!P1_7); Delay_ms(20); key_number = 1; }
	if (!P1_6) { Delay_ms(20); while(!P1_6); Delay_ms(20); key_number = 5; }
	if (!P1_5) { Delay_ms(20); while(!P1_5); Delay_ms(20); key_number = 9; }
	if (!P1_4) { Delay_ms(20); while(!P1_4); Delay_ms(20); key_number = 13;}
	
	P1 = 0xFF;//reset every bit of P1
	P1_2 = 0;
	if (!P1_7) { Delay_ms(20); while(!P1_7); Delay_ms(20); key_number = 2; }
	if (!P1_6) { Delay_ms(20); while(!P1_6); Delay_ms(20); key_number = 6; }
	if (!P1_5) { Delay_ms(20); while(!P1_5); Delay_ms(20); key_number = 10;}
	if (!P1_4) { Delay_ms(20); while(!P1_4); Delay_ms(20); key_number = 14;}
	
	P1 = 0xFF;
	P1_1 = 0;
	if (!P1_7) { Delay_ms(20); while(!P1_7); Delay_ms(20); key_number = 3; }
	if (!P1_6) { Delay_ms(20); while(!P1_6); Delay_ms(20); key_number = 7; }
	if (!P1_5) { Delay_ms(20); while(!P1_5); Delay_ms(20); key_number = 11;}
	if (!P1_4) { Delay_ms(20); while(!P1_4); Delay_ms(20); key_number = 15;}
	
	P1 = 0xFF;
	P1_0 = 0;
	if (!P1_7) { Delay_ms(20); while(!P1_7); Delay_ms(20); key_number = 4; }
	if (!P1_6) { Delay_ms(20); while(!P1_6); Delay_ms(20); key_number = 8; }
	if (!P1_5) { Delay_ms(20); while(!P1_5); Delay_ms(20); key_number = 12;}
	if (!P1_4) { Delay_ms(20); while(!P1_4); Delay_ms(20); key_number = 16;}
	
	return key_number;
}