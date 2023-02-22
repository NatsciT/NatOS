#include "IDT.h"
#include "HAL.h"


static idt_desc _idt[I86_MAX_INTERRUPTS];
static idtr _idtr;



// Internel function declaration
void install_idt(void);
void install_interrupt_handler(uint32 i, uint8 flags, uint16 selector, I86_IRQ_HANDLER handler);
void send_eoi(uint8 irq);

void default_interrupt_handler(void);



void idt_init(uint16 selector)
{
	int i;

	_idtr.limit = sizeof(idt_desc) * I86_MAX_INTERRUPTS;
	_idtr.base = (uint32)&_idt[0];

	memset(&_idt[0], 0, sizeof(idt_desc) * I86_MAX_INTERRUPTS);

	for (i = 0; i < I86_MAX_INTERRUPTS; i++)
		install_interrupt_handler(i, I86_IDT_DESC_PRESENT | I86_IDT_DESC_32BIT_INT,
			selector, default_interrupt_handler);

	install_idt();
}



void install_idt(void)
{
	__asm lidt	[_idtr];
}

void install_interrupt_handler(uint32 i, uint8 flags, uint16 selector, I86_IRQ_HANDLER handler)
{
	if (i >= I86_MAX_INTERRUPTS) return;

	_idt[i].offsetlow = (uint16)((uint32)handler & 0xFFFF);
	_idt[i].offsethigh = (uint16)(((uint32)handler >> 16) & 0xFFFF);
	_idt[i].seg_selector = selector;
	_idt[i].reserved = 0;
	_idt[i].flags = flags;
}

void send_eoi(uint8 irq)
{
	/*
	---- End of Interrupt
	Perhaps the most common command issued to the PIC chips is the end of interrupt (EOI) command (code 0x20).
	This is issued to the PIC chips at the end of an IRQ-based interrupt routine.
	If the IRQ came from the Master PIC, it is sufficient to issue this command only to the Master PIC;
	however if the IRQ came from the Slave PIC, it is necessary to issue the command to both PIC chips.

	From https://wiki.osdev.org/PIC#End_of_Interrupt
	*/

	if (irq >= 8) outb(PORT_PIC2, 0x20);
	outb(PORT_PIC1, 0x20);
}

__declspec(naked) void default_interrupt_handler(void)
{
	__asm
	{
		pushad;
		pushfd;
		cli;
	
		call	send_eoi;

		popfd;
		popad;
		iretd;
	}
}