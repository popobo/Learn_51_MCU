#include "Atmel/REGX52.H"

/**
  * @brief  串口初始�? 4800bps@11.0592MHz
  * @param  �?
  * @retval �?
  */
void Uart_Init()
{
	SCON = 0x50; // 0101 0000
	PCON = 0;
	
	TMOD &= 0x0F;		//设置定时器模�?
	TMOD |= 0x20;		//设置定时器模�?, 8位自动重�?
	TL1 = 0xFA;		//设定定时初�?
	TH1 = 0xFA;		//设定定时器重装�?
	ET1 = 0;		//禁止定时�?1中断
	TR1 = 1;		//启动定时�?1

	EA = 1;
	ES = 1;
}

/**
  * @brief  用串口发送一个字�?
  * @param  发送字�?
  * @retval �?
  */
void Uart_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(!TI);
	TI = 0;
}

/* 串口中断函数
void Uart_Routine() interrupt 4
{
	if(RI)
	{
		P2 = ~SBUF;
		Uart_SendByte(SBUF);
		RI = 0;
	}
}
*/