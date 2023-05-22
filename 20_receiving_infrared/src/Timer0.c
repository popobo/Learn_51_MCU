#include "Atmel/REGX52.H"

/**
  * @brief  定时器初始化函数，100us
  * @param  无
  * @retval 无
  */
void Timer0_Init()		//100微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 0;		//定时器0不计时
}

void Timer0_SetCounter(unsigned int value)
{
    TH0 = value / 256;
    TL0 = value % 256;
}

unsigned int Timer0_GetCounter(void)
{
    return (TH0 << 8) | TL0;
}

void Timer0_Run(unsigned char flag)
{
    TR0 = flag;
}
