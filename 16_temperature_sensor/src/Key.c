#include "Atmel/REGX52.H"
#include "Delay.h"
#include "Key.h"
#include "LCD1602.h"

static unsigned char result_key_num = 0;

/**
  * @brief  获取独立按键key
  * @param  
  * @retval 独立按键key
  */
unsigned char Key()
{
	unsigned char temp = 0;
    temp = result_key_num;
    result_key_num = 0;
	return temp;
}


unsigned char Key_GetState()
{
	unsigned char key_num = 0;
	
	if (!P3_0) { key_num = Key_two; }
	if (!P3_1) { key_num = Key_one; }
	if (!P3_2) { key_num = Key_three; }
	if (!P3_3) { key_num = Key_four; }
	
	return key_num;
}

void Key_Loop(void)
{
    static unsigned char last_key_num = 0;
    static unsigned char current_key_num = 0;
    last_key_num = current_key_num;
    current_key_num = Key_GetState();
    if (last_key_num == Key_one && current_key_num == 0) result_key_num = Key_one;
    if (last_key_num == Key_two && current_key_num == 0) result_key_num = Key_two;
    if (last_key_num == Key_three && current_key_num == 0) result_key_num = Key_three;
    if (last_key_num == Key_four && current_key_num == 0) result_key_num = Key_four;
}