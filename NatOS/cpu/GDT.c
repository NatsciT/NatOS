#include "GDT.h"


static gdt_desc _gdt[MAX_GDT];
static gdtr _gdtr;




void install_gdt(void);
void set_desc(uint32 index, uint32 base, uint32 limit, uint8 access, uint8 gran);



void gdt_init(void)
{
	_gdtr.limit = (uint16)(sizeof(gdt_desc) * MAX_GDT);
	_gdtr.base = (uint32)&_gdt[0];

	memset(&_gdt[0], 0, sizeof(gdt_desc) * MAX_GDT);

	set_desc(0, 0, 0, 0, 0);
	set_desc(1, 0, 0xFFFFFFFF, KERNEL_CODE_DESC_FLAGS, KERNEL_CODE_DESC_GRAN);
	set_desc(2, 0, 0xFFFFFFFF, KERNEL_DATA_DESC_FLAGS, KERNEL_DATA_DESC_GRAN);
	set_desc(3, 0, 0xFFFFFFFF, USER_CODE_DESC_FLAGS, USER_CODE_DESC_GRAN);
	set_desc(4, 0, 0xFFFFFFFF, USER_DATA_DESC_FLAGS, USER_DATA_DESC_GRAN);

	install_gdt();
}



void install_gdt(void)
{ 
	__asm lgdt	[_gdtr];
}

void set_desc(uint32 index, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
	_gdt[index].segment_limit = (uint16)(limit & 0xFFFF);
	_gdt[index].gran = (uint8)((limit >> 16) & 0x0F);

	_gdt[index].base_low = (uint16)(base & 0xFFFF);
	_gdt[index].base_mid = (uint8)((base >> 16) & 0xFF);
	_gdt[index].base_high = (uint8)((base >> 24) & 0xFF);

	_gdt[index].flags = access;
	_gdt[index].gran |= gran & 0xF0;
}