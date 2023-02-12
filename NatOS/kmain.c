#include "kmain.h"


_declspec(naked) void multiboot_entry(void)
{
	__asm
	{
		align 4;

	multiboot_header:
		dd(MULTIBOOT_HEADER_MAGIC);
		dd(MULTIBOOT_HEADER_FLAGS);
		dd(MULTIBOOT_HEADER_CHECKSUM);

		dd(MULTIBOOT_HEADER_ADDR);
		dd(KERNEL_LOAD_ADDR);
		dd(00);
		dd(00);

		dd(MULTIBOOT_HEADER_ADDR + 0x20);

	kernel_entry:
		mov		esp, KERNEL_STACK_ADDR;
		push	0;
		popf;

		push	ebx;
		push	eax;

		call	kmain;

	halt:
		jmp		halt;
	}
}



void kmain(unsigned long magic, unsigned long addr)
{
	vga_console con;

	vga_console_init(&con);
	vga_console_write(&con, "Hello, world!");

	for (;;);
}