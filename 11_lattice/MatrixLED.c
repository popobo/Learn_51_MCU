#include <REGX52.H>
#include "Delay.h"

sbit RCK = P3^5; //RCLK
sbit SCK = P3^6; // SRCLK
sbit SER = P3^4; //SER

#define MARTIX_LED_PORT P0

/**
  * @brief  向74HC595写入一个字节
  * @param  字节
  * @retval 无
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
  * @brief  LED点阵屏显示一列数据
  * @param  col 要显示的列，0~7，0最左
	* @param  要显示的数据
  * @retval 
  */
void MatrixLED_ShowColumn(unsigned char col, unsigned char byte)
{
	// 段选 位选 延时 位清零 ... 消影
	_74HC595_WriteByte(byte);
	MARTIX_LED_PORT = ~(0x80 >> col); 
	Delay_ms(1);
	MARTIX_LED_PORT = 0xFF;
}

/**
  * @brief  初始化
  * @retval 无
  */
void MatrixLED_Init()
{
	SCK = 0;//上电后是高电平，手动置零
	RCK = 0;
}
