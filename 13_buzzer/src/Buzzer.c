#include "Buzzer.h"
#include "Atmel/REGX52.H"
#include "INTRINS.H"

sbit Buzzer_IO = P2^5;

void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

void Buzzer_Time(unsigned char ms)
{
    unsigned char i = 0;
    for (i = 0; i < 2 * ms; ++i)
    {
        Buzzer_IO = !Buzzer_IO;
        Buzzer_Delay500us();    
    }
}