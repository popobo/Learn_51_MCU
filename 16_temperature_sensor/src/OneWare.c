#include "Atmel/REGX52.H"
#include "INTRINS.H"
#include "OneWare.h"

#define DELAY_500US { _nop_(); i = 227; while (--i); }

#define DELAY_70US { _nop_(); i = 29; while (--i); }

#define DELAY_10US { _nop_(); i = 3; while (--i); }

#define DELAY_50US { _nop_(); i = 20; while (--i); }

#define DELAY_5US { _nop_(); _nop_(); _nop_(); _nop_(); }

sbit OneWare_DQ = P3^7;

unsigned char OneWire_Init(void)
{
    unsigned char i = 0;
    unsigned char ack_bit = 0;
    EA = 0;
    OneWare_DQ = 1;
    OneWare_DQ = 0;
	DELAY_500US;

    OneWare_DQ = 1;
    DELAY_70US;
    
    ack_bit = OneWare_DQ;
    DELAY_500US;
    EA = 1;
    return ack_bit;
}

void OneWire_SendBit(unsigned char one_bit)
{
    unsigned char i = 0;
    EA = 0;
    OneWare_DQ = 0;
    DELAY_10US;
    OneWare_DQ = one_bit;
    DELAY_50US;
    OneWare_DQ = 1;
    EA = 1;
}

unsigned char OneWire_ReceiveBit(void)
{
    unsigned char one_bit = 0;
    unsigned char i = 0;
    EA = 0;
    OneWare_DQ = 0;
    DELAY_5US;
    OneWare_DQ = 1;
    DELAY_5US;
    one_bit = OneWare_DQ;
    DELAY_50US;
    EA = 1;
    return one_bit;
}

void OneWare_SendByte(unsigned char byte)
{
    unsigned char i = 0;
    for(i = 0; i < 8; ++i)
    {
        OneWire_SendBit(byte & (0x01 << i));
    }
}

unsigned char OneWare_ReceiveByte(void)
{
    unsigned char i = 0;
    unsigned char byte = 0;
    for(i = 0; i < 8; ++i)
    {
        if(OneWire_ReceiveBit())
        {
            byte |= (0x01 << i);
        }
    }
    return byte;
}