#/bin/bash

### esse arquivo não deve ser modificado
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# compilar
make all

mkdir -p ./boot/isodir/boot/grub
cp ./build/bin/os.bin ./boot/isodir/boot/os.bin
cp ./boot/grub.cfg ./boot/isodir/boot/grub/grub.cfg

# gerar imagem (.iso)
grub-mkrescue -o ./build/iso/os.iso ./boot/isodir