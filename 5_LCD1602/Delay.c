
void Delay_ms(unsigned int ms)		//@12.000MHz
{
	unsigned char i, j;
	while(ms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}