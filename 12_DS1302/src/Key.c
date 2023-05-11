#include "Atmel/REGX52.H"
#include "Delay.h"


/**
  * @brief  获取独立按键key�?
  * @param  �?
  * @retval 独立按键key�?
  */

unsigned char Key()
{
	unsigned char key_num = 0;
	
	if (!P3_0) { Delay_ms(20); while (!P3_0); Delay_ms(20); key_num = 1; }
	if (!P3_1) { Delay_ms(20); while (!P3_1); Delay_ms(20); key_num = 2; }
	if (!P3_2) { Delay_ms(20); while (!P3_2); Delay_ms(20); key_num = 3; }
	if (!P3_3) { Delay_ms(20); while (!P3_3); Delay_ms(20); key_num = 4; }
	
	return key_num;
}
