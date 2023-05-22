#include "Atmel/REGX52.H"
#include "Timer0.h"
#include "Int0.h"
#include "LCD1602.h"

unsigned int IR_time;
unsigned char IR_state;

unsigned char IR_data[4];
unsigned char IR_p_data;

unsigned char IR_data_flag;
unsigned char IR_repeatFlag;
unsigned char IR_address;
unsigned char IR_command;

void IR_Init(void)
{
    Timer0_Init();
    Int0_Init();
}

unsigned char IR_GetDataFlag(void)
{
    if(IR_data_flag)
    {
        IR_data_flag = 0;
        return 1;
    }
    return 0;
}

unsigned char IR_GetRepeatFlag(void)
{
    if(IR_repeatFlag)
    {
        IR_repeatFlag = 0;
        return 1;
    }
    return 0;
}

unsigned char IR_GetAddress(void)
{
    return IR_address;
}

unsigned char IR_GetCommand(void)
{
    return IR_command;
}

void Int0_Routine(void) interrupt 0
{
    switch (IR_state)
    {
    case 0:
    {
        Timer0_SetCounter(0);
        Timer0_Run(1);
        IR_state = 1;
        break;
    }
    case 1:
    {
        IR_time = Timer0_GetCounter();
        Timer0_SetCounter(0);
        if (11900 - 500 < IR_time && IR_time < 11900 + 500) // 12.5 * 952
        {
            IR_state = 2;
        }
        else if (10710 - 500 < IR_time && IR_time < 10710 + 500)
        {
            IR_repeatFlag = 1;
            Timer0_Run(0);
            IR_state = 0;
        }
        else
        {
            IR_state = 0;
        }
    }

    case 2:
    {
        IR_time = Timer0_GetCounter();
        Timer0_SetCounter(0);
        if (1066 - 400 < IR_time && IR_time < 1066 + 400)
        {
            IR_data[IR_p_data / 8] &= ~(0x01 << (IR_p_data % 8));
            IR_p_data++;
        }
        else if (1066 - 400 < IR_time && IR_time < 1066 + 400)
        {
            IR_data[IR_p_data / 8] &= ~(0x01 << (IR_p_data % 8));
            IR_p_data++;
        }
        else if (2142 - 400 < IR_time && IR_time < 2142 + 400)
        {
            IR_data[IR_p_data / 8] |= (0x01 << (IR_p_data % 8));
            IR_p_data++;
        }
        else
        {
            IR_p_data = 0;
            IR_state = 1;
        }
        if (IR_p_data >= 32)
        {
            IR_p_data = 0;
            if((IR_data[0] == ~IR_data[1]) && (IR_data[2] == ~IR_data[3]))
            {
                IR_data_flag = 1;
                IR_address = IR_data[0];
                IR_command = IR_data[2];
                IR_data_flag = 1;
            }
            Timer0_Run(0);
            IR_state = 0;
        }
        LCD_ShowNum(1, 3, IR_p_data, 3);
    }
    }

    LCD_ShowNum(1, 7, IR_state, 2);
}
