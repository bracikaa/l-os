CC=/opt/cross/bin/i686-elf-gcc
CFLAGS= -std=gnu99 -ggdb -m32 -O0 -ffreestanding -O2 -Wall -Wextra
AS=/opt/cross/bin/i686-elf-as


gdt.o : gdt.h gdt.c
	$(CC) $(CFLAGS) -c gdt.c -o gdt.o 

gdt_asm.o : gdt_asm.s
	$(AS) --32 -ggdb gdt_asm.s -o gdt_asm.o

