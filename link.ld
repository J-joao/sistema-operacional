ENTRY(_start)
 
SECTIONS
{
	/* começar pondo as seções à 1 MiB, um jeito convencional dos kernels serem
	   carregados pelo bootloader */
	. = 1M;
 
	/* primeiro pomos o cabeçalho do multiboot, ja que o mesmo é necessario logo no inicio da imagem.
	   depois pomos a seção de código (.text) */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* dados read-only */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
 
	/* dados inicializados */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
 
	/* dados não inicializados e stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
    /* o compilador talvez produza outras seções, por padrão ele irá colocá-las num segmento
       com o mesmo nome, simplesmente adicione oq for necessario aqui */
}