CC=/opt/cross/bin/i686-elf-gcc
AS=/opt/cross/bin/i686-elf-as
KERNEL_IMG=myos.bin
GRUB=grub.cfg
OBJECTS=terminal.o \
	boot.o \
	port.o \
	kernel.o \
	pic.o \
	common.o \
	gdt.o \
	gdt_assembly.o \
	idt.o \
	idt_assembly.o\
	isr.o \
	keyboard.o \


CFLAGS= -std=gnu99 -ggdb -m32 -O0 -ffreestanding -O2 -Wall -Wextra


all: $(KERNEL_IMG)

clean:
	-@rm *.o *~


kernel.o : kernel.c terminal.h gdt.h idt.h pic.h keyboard.h
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

terminal.o : terminal.h terminal.c 
	$(CC) $(CFLAGS) -c terminal.c -o terminal.o

common.o : common.h common.c
	$(CC) $(CFLAGS) -c common.c -o common.o

boot.o : boot.s
	$(AS) --32 -ggdb boot.s -o boot.o

port.o : port.s
	$(AS) --32 -ggdb port.s -o port.o

gdt_assembly.o : gdt_assembly.s
	$(AS) --32 -ggdb gdt_assembly.s -o gdt_assembly.o

idt_assembly.o : idt_assembly.s
	$(AS) --32 -ggdb idt_assembly.s -o idt_assembly.o

pic.o : pic.c pic.h port.h terminal.h
	$(CC) $(CFLAGS) -c pic.c -o pic.o

keyboard.o : keyboard.c keyboard.h
	$(CC) $(CFLAGS) -c keyboard.c -o keyboard.o


gdt.o : gdt.c gdt.h terminal.h
	$(CC) $(CFLAGS) -c gdt.c -o gdt.o

idt.o : idt.c idt.h terminal.h common.h
	$(CC) $(CFLAGS) -c idt.c -o idt.o

isr.o : isr.c isr.h terminal.h pic.h port.h
	$(CC) $(CFLAGS) -c isr.c -o isr.o

$(KERNEL_IMG) : $(OBJECTS) linker.ld
	$(CC) -m32 -ggdb -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc
