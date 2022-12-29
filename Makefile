.PHONY: clean

OBJFILES=./build/obj/boot.o ./build/obj/string.o ./build/obj/vga.o ./build/obj/memory.o \
		 ./build/obj/kernel.o

CFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra

all: 
### gerar o arquivo objeto do cabeçalho multiboot 
	nasm -f elf32 ./boot/boot.asm -o ./build/obj/boot.o
	
### gerar os arquivos objeto das bibliotecas na pasta "inc"
	i686-elf-gcc -c ./inc/string.c -o ./build/obj/string.o $(CFLAGS)
	i686-elf-gcc -c ./inc/vga.c -o ./build/obj/vga.o $(CFLAGS)
	i686-elf-gcc -c ./inc/memory/memory.c -o ./build/obj/memory.o $(CFLAGS)
	
### gerar o arquivo objeto do kernel
	i686-elf-gcc -c ./kernel/kernel.c -o ./build/obj/kernel.o $(CFLAGS)
	
### fazer a linkagem dos arquivos objeto
	i686-elf-gcc -T link.ld -o ./build/bin/os.bin -ffreestanding -nostdlib $(OBJFILES) -lgcc

clean:
	-rm ./build/iso/*.iso
	-rm ./build/bin/*.bin
	-rm ./build/obj/*.o
	-rm -rf ./boot/isodir/