#include "gdt.h"

GDT gdt[3];
GDT_pointer gdt_ptr;

void init_gdt()
{
	gdt_ptr.limit = (sizeof(GDT) * 3) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	gdt_set_gate(0,0,0,0,0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	//terminal_writestring("Initializing GDT.\n");
	gdt_flush(&gdt_ptr);
}

static void gdt_set_gate(int32_t entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	//descriptor base adress
	gdt[entry].base_low = (base & 0xFFFF);
	gdt[entry].base_high = (base >> 16) & 0xFF;
	gdt[entry].base_high = (base >> 24) & 0xFF;

	//descriptor limits	
	gdt[entry].limit_low = (limit & 0xFFFF);
	gdt[entry].granularity = ((limit >> 16) & 0x0F);
	
	//granularity/access flags
	gdt[entry].granularity |= (gran & 0xF0);
	gdt[entry].access_byte = access;
}
