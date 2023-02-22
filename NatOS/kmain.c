#include "kmain.h"



// Internel function declaration
void multiboot_entry(void);
void hardware_init(void);



static vga_console con;


void kmain(unsigned long magic, unsigned long addr)
{
	vga_console_init(&con);
	hardware_init();

	vga_console_write(&con, "Hello, world!\n");
	vga_console_set_color_text(&con, light_cyan);
	vga_console_write(&con, "magic: %x\naddr: %x", magic, addr);

	for (;;);
}



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

void hardware_init(void)
{
	gdt_init();
	idt_init(0x8);
}