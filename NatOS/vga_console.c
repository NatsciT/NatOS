#include "vga_console.h"



// Internel function declaration
void cursor_move_front(vga_console* pVgaConsole);
void cursor_move_back(vga_console* pVgaConsole);
void cursor_move_up(vga_console* pVgaConsole);
void cursor_move_down(vga_console* pVgaConsole);

void screen_scroll_down(vga_console* pVgaConsole);



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


void vga_console_write(vga_console* pVgaConsole, const char* string, ...)
{
	byte* ap = (byte*)((int*)(&string) + 1);
	unsigned int i = 0;
	char temp[MAX_DIGITS] = { 0, };

	while (string[i])
	{
		if (string[i] == '%')
		{
			switch (string[++i])
			{
			case 'c':
				vga_console_writechar(pVgaConsole, (char)*(int*)ap);
				ap += sizeof(int);
				break;

			case 's':
				vga_console_write(pVgaConsole, *(const char**)ap);
				ap += sizeof(const char*);
				break;

			case 'd':
			case 'i':
				int_to_string(*(int*)ap, temp);
				vga_console_write(pVgaConsole, temp);
				ap += sizeof(int);
				break;

			case 'x':
				hex_to_string(*(int*)ap, temp);
				vga_console_write(pVgaConsole, temp);
				ap += sizeof(int);
				break;

			default:
				i--;
				break;
			}
		}
		else
			vga_console_writechar(pVgaConsole, string[i]);

		i++;
	}
}

void vga_console_writechar(vga_console* pVgaConsole, char ch)
{
	unsigned short color = (unsigned short)((pVgaConsole->background_color << 4) | (pVgaConsole->text_color));

	if (ch == '\n')
	{
		pVgaConsole->cursor_x = 0;
		cursor_move_down(pVgaConsole);
	}
	else if (ch < ' ')
		return;
	else
	{
		pVgaConsole->vga_addr[pVgaConsole->cursor_y * VGA_SCREEN_WIDTH + pVgaConsole->cursor_x] = (color << 8) | (unsigned short)ch;
		cursor_move_front(pVgaConsole);
	}
}



void vga_console_set_color_text(vga_console* pVgaConsole, vga_console_color color)
{
	pVgaConsole->text_color = color;
}

void vga_console_set_color_background(vga_console* pVgaConsole, vga_console_color color)
{
	pVgaConsole->background_color = color;
}



void cursor_move_front(vga_console* pVgaConsole)
{
	pVgaConsole->cursor_x++;

	if (pVgaConsole->cursor_x >= VGA_SCREEN_WIDTH)
	{
		pVgaConsole->cursor_x = 0;
		cursor_move_down(pVgaConsole);
	}
}

void cursor_move_back(vga_console* pVgaConsole)
{
	pVgaConsole->cursor_x--;

	if (pVgaConsole->cursor_x < 0)
	{
		pVgaConsole->cursor_x = VGA_SCREEN_WIDTH - 1;
		cursor_move_up(pVgaConsole);
	}
}

void cursor_move_up(vga_console* pVgaConsole)
{
	pVgaConsole->cursor_y--;

	if (pVgaConsole->cursor_y < 0)
		pVgaConsole->cursor_y = 0;
}

void cursor_move_down(vga_console* pVgaConsole)
{
	pVgaConsole->cursor_y++;

	if (pVgaConsole->cursor_y >= VGA_SCREEN_HEIGHT)
	{
		screen_scroll_down(pVgaConsole);
		pVgaConsole->cursor_y--;
	}
}

void screen_scroll_down(vga_console* pVgaConsole)
{
	memcpy(
		(byte*)&(pVgaConsole->vga_addr[VGA_SCREEN_WIDTH]),
		(byte*)pVgaConsole->vga_addr,
		sizeof(unsigned short) * VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT
	);
}