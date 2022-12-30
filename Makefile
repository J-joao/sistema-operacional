.PHONY: clean

BUILDDIR=./build
SRCDIR=./src

OBJFILES=$(BUILDDIR)/obj/boot.o $(BUILDDIR)/obj/string.o $(BUILDDIR)/obj/vga.o $(BUILDDIR)/obj/memory.o \
		 $(BUILDDIR)/obj/useful.o $(BUILDDIR)/obj/io.o $(BUILDDIR)/obj/logs.o \
		 $(BUILDDIR)/obj/kernel.o

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
	nasm -f elf32 $(SRCDIR)/boot/boot.asm -o $(BUILDDIR)/obj/boot.o
	
### gerar os arquivos objeto das bibliotecas na pasta "inc"
	i686-elf-gcc -c $(SRCDIR)/inc/string.c -o $(BUILDDIR)/obj/string.o $(CFLAGS)
	i686-elf-gcc -c $(SRCDIR)/inc/vga/vga.c -o $(BUILDDIR)/obj/vga.o $(CFLAGS)
	i686-elf-gcc -c $(SRCDIR)/inc/memory/memory.c -o $(BUILDDIR)/obj/memory.o $(CFLAGS)
	i686-elf-gcc -c $(SRCDIR)/inc/useful/useful.c -o $(BUILDDIR)/obj/useful.o $(CFLAGS)
	i686-elf-gcc -c $(SRCDIR)/inc/IO/io.c -o $(BUILDDIR)/obj/io.o $(CFLAGS)
	i686-elf-gcc -c $(SRCDIR)/inc/debug/logs/logs.c -o $(BUILDDIR)/obj/logs.o $(CFLAGS)

### gerar o arquivo objeto do kernel
	i686-elf-gcc -c $(SRCDIR)/kernel/kernel.c -o $(BUILDDIR)/obj/kernel.o $(CFLAGS)
	
	$(call emit_action, "LINKING BINARIES")
### fazer a linkagem dos arquivos objeto
	i686-elf-gcc -T link.ld -o $(BUILDDIR)/bin/os.bin -ffreestanding -nostdlib $(OBJFILES) -lgcc

clean:
	$(call emit_action, "CLEANING DIRECTORIES")
	-rm $(BUILDDIR)/iso/*.iso
	-rm $(BUILDDIR)/bin/*.bin
	-rm $(BUILDDIR)/obj/*.o
	-rm -rf ./boot/isodir/