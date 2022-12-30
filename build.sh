#/bin/bash

### esse arquivo não deve ser modificado
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# compilar
make all

mkdir -p ./src/boot/isodir/boot/grub
cp ./build/bin/os.bin ./src/boot/isodir/boot/os.bin
cp ./src/boot/grub.cfg ./src/boot/isodir/boot/grub/grub.cfg

# gerar imagem (.iso)
echo -e "\033[92m++++++++++GENERATING ISO IMAGE++++++++++\033[0m"
grub-mkrescue -o ./build/iso/os.iso ./src/boot/isodir