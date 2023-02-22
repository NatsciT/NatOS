#pragma once

#include "../common.h"

#define I86_MAX_INTERRUPTS	256

// flags
#define I86_IDT_DESC_TASK_GATE	0b00000101
#define I86_IDT_DESC_16BIT_INT	0b00000110
#define I86_IDT_DESC_16BIT_TRAP	0b00000111
#define I86_IDT_DESC_32BIT_INT	0b00001110
#define I86_IDT_DESC_32BIT_TRAP	0b00001111

#define I86_IDT_DESC_RING1	0b00100000
#define I86_IDT_DESC_RING2	0b01000000
#define I86_IDT_DESC_RING3	0b01100000

#define I86_IDT_DESC_PRESENT	0b10000000



#define PORT_PIC1	0x20
#define PORT_PIC2	0xA0

#pragma pack(push, 1)

typedef struct __idt_desc
{
	uint16 offsetlow;
	uint16 seg_selector;
	uint8 reserved;
	uint8 flags;
	uint16 offsethigh;
} idt_desc;

typedef struct __idtr
{
	uint16 limit;
	uint32 base;
} idtr;

#pragma pack(pop)

typedef void(__cdecl* I86_IRQ_HANDLER)(void);



void idt_init(uint16 selector);