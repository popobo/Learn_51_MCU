#include <REGX52.H>

/**
  * @brief  串口初始化 4800bps@11.0592MHz
  * @param  无
  * @retval 无
  */
void Uart_Init()
{
	SCON = 0x40; // 0100 0000
	PCON = 0;
	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式, 8位自动重装
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

/**
  * @brief  用串口发送一个字节
  * @param  发送字节
  * @retval 无
  */
void Uart_SendByte(char Byte)
{
	SBUF = Byte;
	while(!TI);
	TI = 0;
}