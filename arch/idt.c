#include "idh.h"
#include "../lib/string.h"

extern void idt_flush(IDT_ptr *);

static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

IDT idt_entries[256];
IDT_ptr idt_pointer;

void idt_install()
{
	idt_pointer.limit = (sizeof(struct IDT) * 256) - 1);
}
