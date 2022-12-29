# para compilar:

**primeiro dê permição para o script montador**
```
sudo chmod +wrx ./build.sh
```

**depois rode o script montador**
```
./build.sh
```

**para abrir o sistema operacional em uma maquina virtual, use qemu, com o seguinte comando**
```
qemu-system-i386 -cdrom ./build/iso/os.iso
```

se quiser limpar as pastas de montagem
```
make clean
```
