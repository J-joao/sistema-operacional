MBALIGN  equ  1 << 0                ; alinhar os módulos carregados nos limites da página
MEMINFO  equ  1 << 1                ; fornecer mapeamento da memoria
FLAGS    equ  MBALIGN | MEMINFO     ; essa é a flag do campo de multiboot
MAGIC    equ  0x1BADB002            ; "numero magico" serve para o bootloader nos encontrar
CHECKSUM equ -(MAGIC + FLAGS)       ; checksum, para provar que somos multiboot

; declarar um cabeçalho de multiboot que marque o programa como um kernel. Estes são numeros
; magicos que estão documentados no padrão de multiboot. O bootloader irá
; procurar por esta assinatura nos primeiros 8 KiB do arquivo do kernel, alinhados em um
; limite de 32 bits. A assinatura está em sua própria seção para que o cabeçalho possa ser
; forçado a estar dentro dos primeiros 8 KiB do arquivo do kernel.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; O padrão de multiboot não define o valor do registrador do ponteiro do stack
; (esp) e cabe ao kernel fornecer um stack. aqui nos alocamos espaço para um
; pequeno stack criando um símbolo na parte inferior e, em seguida, alocando 16384
; bytes para que, finalmente, seja criado um símbolo no topo. (o stack cresce
; para baixo na arquitetura x86). o stack está em sua própria seção para que possa ser marcada 
; como nobits, o que significa que o arquivo do kernel é menor ja que ele não contém um
; stack não inicializado. o stack na arquitetura x86 deve estar alinhado usando 16 bytes de acordo com o
; Padrão System V ABI e extensões de-facto. O compilador assumirá que o
; stack está devidamente alinhado e a falha em alinhar o stack resultará em comportamento estranho.
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

; O script do linker (link.ld) especifica "_start" como o ponto de entrada para o kernel e o
; o bootloader saltará para este ponto assim que o kernel for carregado. Com isso, fica claro que
; não faz sentido retornar desta função ja que o bootloader ja fez seu trabalho.
section .text
; aqui declaramos "_start" como um símbolo de função com o tamanho de símbolo fornecido.
global _start:function (_start.end - _start)

_start:
	mov esp, stack_top

    ; exportar a função de entrada do kernel
	extern kernel_entry
    ; chamar a função de entrada do kernel (definida no arquivo kernel.c)
	call kernel_entry
	; limpar interrupts
    cli
    
; loop infinito
.hang:	
    hlt
	jmp .hang

.end: