#include "Atmel/REGX52.H"
#include "Delay.h"
#include "LCD1602.h"
#include "Int0.h"
#include "Timer0.h"
#include "IR.h"

unsigned char num;
unsigned int time;
unsigned char address;
unsigned char command;

void main()
{
    LCD_Init();
    LCD_ShowString(1, 1, "A");
    IR_Init();
    while(1)
    {
        if(IR_GetDataFlag())
        {
            address = IR_GetAddress();
            command = IR_GetCommand();

            LCD_ShowHexNum(2, 1, address, 2);
            LCD_ShowHexNum(2, 5, command, 2);
        }
    }
}
