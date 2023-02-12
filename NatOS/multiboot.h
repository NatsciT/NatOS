#pragma once

#define dd(x)							\
		__asm _emit (x)			& 0xff	\
		__asm _emit (x) >> 8	& 0xff	\
		__asm _emit (x) >> 16	& 0xff	\
		__asm _emit (x) >> 24	& 0xff

// Kernel load constants
#define KERNEL_LOAD_ADDR	0x00100000
#define KERNEL_STACK_ADDR	0x00004000
#define ALIGN				0x0400

// Multiboot header constants
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002
#define MULTIBOOT_HEADER_FLAGS		0x00010003
#define MULTIBOOT_HEADER_CHECKSUM	-(MULTIBOOT_HEADER_MAGIC+MULTIBOOT_HEADER_FLAGS)

#define MULTIBOOT_HEADER_ADDR		KERNEL_LOAD_ADDR+ALIGN