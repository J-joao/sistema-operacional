.PHONY: clean

GCC=gcc -m32
NASM=nasm

BUILDDIR=./build
SRCDIR=./src

OBJFILES=$(BUILDDIR)/obj/boot.o $(BUILDDIR)/obj/string.o $(BUILDDIR)/obj/vga.o $(BUILDDIR)/obj/memory.o \
		 $(BUILDDIR)/obj/useful.o $(BUILDDIR)/obj/io.o $(BUILDDIR)/obj/logs.o $(BUILDDIR)/obj/gdt_idt_asm.o \
		 $(BUILDDIR)/obj/interrupts.o $(BUILDDIR)/obj/gdt.o $(BUILDDIR)/obj/idt.o $(BUILDDIR)/obj/isr.o \
		 $(BUILDDIR)/obj/panic.o $(BUILDDIR)/obj/kb.o $(BUILDDIR)/obj/kernel.o		 

CFLAGS=-std=gnu99 -ffreestanding -Wextra

define emit_action
@echo "\033[92m++++++++++"${1}"++++++++++\033[0m"
endef

all: 
	$(call emit_action, "CREATING BUILD DIRECTORIES")
	-mkdir $(BUILDDIR)/
	-mkdir $(BUILDDIR)/iso/
	-mkdir $(BUILDDIR)/bin/
	-mkdir $(BUILDDIR)/obj/

	$(call emit_action, "GENERATING OBJ FILES")
### gerar o arquivo objeto do cabeçalho multiboot 
	$(NASM) -f elf32 $(SRCDIR)/boot/boot.asm -o $(BUILDDIR)/obj/boot.o
	
### gerar os arquivos objeto das bibliotecas na pasta "inc"
	$(GCC) -c $(SRCDIR)/inc/string.c -o $(BUILDDIR)/obj/string.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/vga/vga.c -o $(BUILDDIR)/obj/vga.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/memory/memory.c -o $(BUILDDIR)/obj/memory.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/useful/useful.c -o $(BUILDDIR)/obj/useful.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/IO/io.c -o $(BUILDDIR)/obj/io.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/inc/debug/logs/logs.c -o $(BUILDDIR)/obj/logs.o $(CFLAGS)

### gerar os arquivos objeto dos arquivos na pasta "kernel/arch/i386"
	$(NASM) -f elf32 $(SRCDIR)/kernel/arch/i386/gdt_idt.asm -o $(BUILDDIR)/obj/gdt_idt_asm.o
	$(NASM) -f elf32 $(SRCDIR)/kernel/arch/i386/interrupt_handlers/interrupts.asm -o $(BUILDDIR)/obj/interrupts.o

	$(GCC) -c $(SRCDIR)/kernel/arch/i386/gdt/gdt.c -o $(BUILDDIR)/obj/gdt.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/kernel/arch/i386/idt/idt.c -o $(BUILDDIR)/obj/idt.o $(CFLAGS)
	$(GCC) -c $(SRCDIR)/kernel/arch/i386/interrupt_handlers/isr.c -o $(BUILDDIR)/obj/isr.o $(CFLAGS)
	
### gerar os arquivos objetos de kernel/panic/
	$(GCC) -c $(SRCDIR)/kernel/panic/panic.c -o $(BUILDDIR)/obj/panic.o $(CFLAGS)

### gerar os arquivos objetos de kernel/drivers/
	$(GCC) -c $(SRCDIR)/kernel/drivers/keyboard/kb.c -o $(BUILDDIR)/obj/kb.o $(CFLAGS)

### gerar o arquivo objeto do kernel
	$(GCC) -c $(SRCDIR)/kernel/kernel.c -o $(BUILDDIR)/obj/kernel.o $(CFLAGS)
	
	$(call emit_action, "LINKING BINARIES")
### fazer a linkagem dos arquivos objeto
	$(GCC) -T link.ld -o $(BUILDDIR)/bin/os.bin -ffreestanding -nostdlib $(OBJFILES) -lgcc

clean:
	$(call emit_action, "CLEANING DIRECTORIES")
	-rm $(BUILDDIR)/iso/*.iso
	-rm $(BUILDDIR)/bin/*.bin
	-rm $(BUILDDIR)/obj/*.o
	-rm -rf ./boot/isodir/