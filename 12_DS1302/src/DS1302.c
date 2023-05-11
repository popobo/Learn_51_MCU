#include "Atmel/REGX52.H"
#include "DS1302.h"

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define DEC2BCD(x) ((x) / 10 * 16 + (x) % 10)
#define BCD2DEC(x) ((x) / 16 * 10 + (x) % 16)

unsigned char DS1302_Time[] = {23, 5, 11, 15, 05, 0, 4};

void DS1302_Init(void)
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
}

void DS1302_WriteByte(unsigned char cmd, unsigned char byte)
{
    unsigned char i = 0;
    DS1302_CE = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = cmd & (0x01 << i);
        DS1302_SCLK = 1;
        // 需要判断需要加延时增加高电平时间
        DS1302_SCLK = 0;
    }

    for (i = 0; i < 8; i++)
    {
        DS1302_IO = byte & (0x01 << i);
        DS1302_SCLK = 1;
        // 需要判断需要加延时增加高电平时间
        DS1302_SCLK = 0;
    }
    DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char cmd)
{
    unsigned char i = 0, byte = 0x00;
    cmd |= 0x01;
    DS1302_CE = 1;
    for (i = 0; i < 8; i++)
    {
        DS1302_IO = cmd & (0x01 << i);
        DS1302_SCLK = 0; // 先给低再给高
        // 需要判断需要加延时增加高电平时间
        DS1302_SCLK = 1;
    }

    for (i = 0; i < 8; i++)
    {
        DS1302_SCLK = 1;
        // 需要判断需要加延时增加高电平时间
        DS1302_SCLK = 0;
        if(DS1302_IO)
        {
            byte |= (0x01 << i);
        }
    }

    DS1302_CE = 0;
    DS1302_IO = 0;
    return BCD2DEC(byte);
}

void DS1302_SetTime(void)
{
    DS1302_WriteByte(DS1302_WP, 0x00);
    DS1302_WriteByte(DS1302_YEAR, DEC2BCD(DS1302_Time[0]));
    DS1302_WriteByte(DS1302_MONTH, DEC2BCD(DS1302_Time[1]));
    DS1302_WriteByte(DS1302_DATE, DEC2BCD(DS1302_Time[2]));
    DS1302_WriteByte(DS1302_HOUR, DEC2BCD(DS1302_Time[3]));
    DS1302_WriteByte(DS1302_MINUTE, DEC2BCD(DS1302_Time[4]));
    DS1302_WriteByte(DS1302_SECOND, DEC2BCD(DS1302_Time[5]));
    DS1302_WriteByte(DS1302_DAY, DEC2BCD(DS1302_Time[6]));
    DS1302_WriteByte(DS1302_WP, 0x80);
}

void DS1302_GetTime(void)
{
    DS1302_Time[0] = DS1302_ReadByte(DS1302_YEAR);
    DS1302_Time[1] = DS1302_ReadByte(DS1302_MONTH);
    DS1302_Time[2] = DS1302_ReadByte(DS1302_DATE);
    DS1302_Time[3] = DS1302_ReadByte(DS1302_HOUR);
    DS1302_Time[4] = DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Time[5] = DS1302_ReadByte(DS1302_SECOND);
    DS1302_Time[6] = DS1302_ReadByte(DS1302_DAY);
}