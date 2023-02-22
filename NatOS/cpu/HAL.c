#include "HAL.h"


__declspec(naked) void outb(uint16 port, uint8 num)
{
	__asm
	{
		push	eax;
		push	edx;

		movzx	edx, port;
		movzx	eax, num;
		out		dx, al;

		pop		edx;
		pop		eax;
	}
}