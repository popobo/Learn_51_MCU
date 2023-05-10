
void Delay_ms(unsigned int ms)		//@11.0592MHz
{
	unsigned char i, j;
	while(ms--)
	{
        i = 2;
        j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}