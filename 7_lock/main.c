#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "matrix.h"

#define PASS_WORD_LEN 4
#define PASSWORD "1234"

void print_password(char * password)
{
		unsigned char i = 0;
		for(i = 0; i < PASS_WORD_LEN; ++i)
		{
				LCD_ShowChar(2, i + 1, password[i]);
		}
}

void main()
{
    unsigned char index = 0;
    char password[PASS_WORD_LEN];
		unsigned char i = 0;
	
		for(i = 0; i < PASS_WORD_LEN; ++i)
		{
				password[i] = '-';
		}
		
		LCD_Init();
		LCD_ShowString(1, 1, "Password");
		
		print_password(password);
    while(1)
		{
				unsigned key_number = MatrixKey();
				char * c_p = PASSWORD;
			
			  if(!key_number)
					continue;
				
        if(key_number <= 10)
        {
            password[index] = '0' + (key_number % 10);
            index++;
						print_password(password);
        }
        else if (key_number == 11 || index >= PASS_WORD_LEN)
        {
            for(i = 0; i < PASS_WORD_LEN; ++i)
            {
                if(c_p[i] != password[i])
                    break;
            }
            if (i != PASS_WORD_LEN)
            {
                LCD_ShowString(1, 13, " ERR");
            }
            else
            {
                LCD_ShowString(1, 13, "PASS");
            }
            index = 0;
        }
        else if (key_number == 12)
        {
            for(i = 0; i < PASS_WORD_LEN; ++i)
            {
                password[i] = '-';
            }
						index = 0;
						print_password(password);
        }
    }
}