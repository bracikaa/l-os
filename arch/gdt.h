#ifndef GDT_H
#define GDT_H

#include <stdint.h>
// It contains entries telling the CPU about memory segments.
// We will load it using the LGDT assembly instruction.

struct gdt_struct
{
	uint16_t limit_low; //0-15
	uint16_t base_low; //16-31
	uint8_t base_middle; //32-39
	uint8_t access_byte;//40-47
	uint8_t granularity; //48-55, 48-51 limit, 52-55 flags
	uint8_t base_high; //56-63	
} __attribute__((packed));

typedef struct gdt_struct GDT;

struct gdt_ptr_struct
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

typedef struct gdt_ptr_struct GDT_pointer;

void init_gdt();
extern void gdt_flush(GDT_pointer*);
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

#endif
