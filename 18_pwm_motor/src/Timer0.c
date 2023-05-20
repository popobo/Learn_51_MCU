#include "Atmel/REGX52.H"

/**
  * @brief  定时器初始化函数，100us
  * @param  �?
  * @retval �?
  */
void Timer0_Init()		//100微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模�?
	TMOD |= 0x01;		//设置定时器模�?
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时�?0开始计�?
	
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}

/*
void Timer0_Routine() interrupt TF0_VECTOR
{
    static unsigned int t0_count = 0;
    TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
    t0_count++;
    if (t0_count >= 1000)
    {
        t0_count = 0;
        if (mode == edit_mode)
            flick_flag = !flick_flag;
    }
}
*/