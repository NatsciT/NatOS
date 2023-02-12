#include "conv.h"
#include "types.h"


void int_to_string(int num, char* buffer)
{
	int i = 1;
	int pos = 0;
	int temp = 0;
	
	if (num < 0)
	{
		num *= -1;
		buffer[pos++] = '-';
	}
	else if (num == 0)
	{
		buffer[0] = int_to_ascii(0);
		buffer[1] = 0;
		return;
	}

	while (i <= num) i *= 10;
	while (i > 1)
	{
		i /= 10;
		temp = num / i;

		buffer[pos++] = (char)int_to_ascii(temp);
		num -= temp * i;
	}

	buffer[pos] = 0;
}