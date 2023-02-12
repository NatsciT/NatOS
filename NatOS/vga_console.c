#include "vga_console.h"



void vga_console_init(vga_console* pVgaConsole)
{
	pVgaConsole->vga_addr =
		(*(unsigned short*)0x410 & 0x30) == 0x30 ?
		(unsigned short*)0xb0000 :
		(unsigned short*)(0xb8000);

	pVgaConsole->cursor_x = 0;
	pVgaConsole->cursor_y = 0;

	pVgaConsole->text_color = white;
	pVgaConsole->background_color = black;

	vga_console_clear(pVgaConsole);
}

void vga_console_clear(vga_console* pVgaConsole)
{
	unsigned int i;
	unsigned short color = (unsigned short)((pVgaConsole->background_color << 4) | pVgaConsole->text_color);

	for (i = 0; i < VGA_SCREEN_HEIGHT * VGA_SCREEN_WIDTH; i++)
	{
		pVgaConsole->vga_addr[i] = (color << 8) | ' ';
	}

	pVgaConsole->cursor_x = 0;
	pVgaConsole->cursor_y = 0;
}



//void vga_console_write_fmt(vga_console* pVgaConsole, const char* string, ...)
//{
//	int* ap = &string;
//
//
//}

void vga_console_write(vga_console* pVgaConsole, const char* string)
{
	unsigned int i = 0;

	while (string[i])
	{
		vga_console_writechar(pVgaConsole, string[i]);
		i++;
	}
}

void vga_console_writechar(vga_console* pVgaConsole, char ch)
{
	unsigned short color = (unsigned short)((pVgaConsole->background_color << 4) | (pVgaConsole->text_color));

	if (ch == '\r')
		pVgaConsole->cursor_x = 0;
	else if (ch == '\n')
		pVgaConsole->cursor_y++;
	else if (ch < ' ')
		return;
	else
		pVgaConsole->vga_addr[pVgaConsole->cursor_x++] = (color << 8) | (unsigned short)ch;

	if (pVgaConsole->cursor_x >= VGA_SCREEN_WIDTH)
	{
		pVgaConsole->cursor_x = 0;
		pVgaConsole->cursor_y++;
	}
}