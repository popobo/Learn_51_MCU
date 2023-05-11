#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "matrix.h"
#include "timer0.h"
#include "INTRINS.h"
#include "Key.h"
#include "Uart.h"

void main()
{
	Uart_Init();
	while(1)
	{
	}
}


void Uart_Routine() interrupt 4
{
	if(RI)
	{
		P2 = ~SBUF;
		Uart_SendByte(SBUF);
		RI = 0;
	}
}