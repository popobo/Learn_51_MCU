#include <REGX52.H>

void Delay_ms(unsigned int ms)		//@11.0592MHz
{
	while(ms--)
	{
		unsigned char i, j;

        i = 2;
        j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}

void main()
{

	/*
	while(1)
	{
		P2_0 = P3_1;
	}
	*/
	
	/*
	while(1)
	{
		if (!P3_1)
		{
			Delay_ms(20);
			while (!P3_1);
			Delay_ms(20);
			P2_0 = ~P2_0;
		}
	}
	*/
	
	
	/*
	unsigned char led_num = 0;
	
	while(1)
	{
		if (!P3_1)
		{
			Delay_ms(20);
			while (!P3_1);
			Delay_ms(20);
			led_num++;
			P2 = ~led_num;
		}
	}
	*/
	
	unsigned char led_num = 1;
	
	while(1)
	{
		if (!P3_1)
		{
			Delay_ms(20);
			while (!P3_1);
			Delay_ms(20);
			led_num = led_num << 1;
			if (led_num == 0)
			{
				led_num = 1;
			}
			P2 = ~led_num;
		}
		
		if (!P3_0)
		{
			Delay_ms(20);
			while (!P3_0);
			Delay_ms(20);
			led_num = led_num >> 1;
			if (led_num == 0)
			{
				led_num = 0x80;
			}
			P2 = ~led_num;
		}
	}
	
}