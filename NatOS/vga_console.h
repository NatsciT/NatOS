#pragma once

#include "common.h"

#define VGA_SCREEN_WIDTH	80
#define VGA_SCREEN_HEIGHT	25



typedef enum
{
	black, blue, green, cyan, red, magenta, brown, light_gray,
	dark_gray, light_blue, light_green, light_cyan, light_red, pink, yellow, white
} vga_console_color;

typedef struct __console
{
	unsigned short* vga_addr;

	vga_console_color text_color;
	vga_console_color background_color;

	unsigned short cursor_x;
	unsigned short cursor_y;
} vga_console;



void vga_console_init(vga_console*);
void vga_console_clear(vga_console*);

void vga_console_write(vga_console*, const char*);
void vga_console_writechar(vga_console*, char);
void vga_console_writefmt(vga_console*, const char*, ...);

void vga_console_set_color_text(vga_console*, vga_console_color);
void vga_console_set_color_background(vga_console*, vga_console_color);