#include "Atmel/REGX52.H"
#include "Delay.h"

sbit RCK = P3^5; //RCLK
sbit SCK = P3^6; // SRCLK
sbit SER = P3^4; //SER

#define MARTIX_LED_PORT P0

/**
  * @brief  74HC595写入一个字
  * @param  字节
  * @retval 
  */
void _74HC595_WriteByte(unsigned char byte)
{
	unsigned char i;
	for(i = 0; i < 8; ++i)
	{
		SER = byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
}

/**
  * @brief  LED点阵屏显示一列数
  * @param  col 要显示的列，0~70最
	* @param  要显示的数据
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char col, unsigned char byte)
{
	// 段 位 延时 位清 ... 消影
	_74HC595_WriteByte(byte);
	MARTIX_LED_PORT = ~(0x80 >> col); 
	Delay_ms(1);
	MARTIX_LED_PORT = 0xFF;
}

/**
  * @brief  初始
  * @retval 
  */
void MatrixLED_Init()
{
	SCK = 0;//上电后是高电平，手动置零
	RCK = 0;
}
