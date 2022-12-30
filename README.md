# para compilar:

**primeiro dê permição para o script montador**
```
sudo chmod +wrx ./build.sh
```

**depois rode o script montador**
```
./build.sh
```

**para abrir o sistema operacional em uma maquina virtual, use qemu, com o seguinte comando:**
```
qemu-system-i386 -debugcon file:kernel_logs.log -cdrom ./build/iso/os.iso
```

**para rodar o sistema operacional no seu próprio computador, use dd para escrever a imagem para uma mídia bootavel**
```
sudo dd if=./build/iso/os.iso of=/dev/sdx
```

se quiser limpar as pastas de montagem
```
make clean
```
