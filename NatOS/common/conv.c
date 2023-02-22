#include "conv.h"
#include "types.h"



// Internel function declaration
char num_to_hex_char(int num);


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
		buffer[0] = '0';
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

void hex_to_string(int hex, char* buffer)
{
	int i;
	int pos = 2;

	buffer[0] = '0';
	buffer[1] = 'x';

	for (i = 28; i >= 0; i -= 4)
		buffer[pos++] = num_to_hex_char((hex >> i) & 0b1111);
}



char num_to_hex_char(int num)
{
	if (num >= 0 && num <= 9)
		return int_to_ascii(num);

	switch (num)
	{
	case 0xA:
		return 'A';
	case 0xB:
		return 'B';
	case 0xC:
		return 'C';
	case 0xD:
		return 'D';
	case 0xE:
		return 'E';
	case 0xF:
		return 'F';
	default:
		return '?';
	}
}