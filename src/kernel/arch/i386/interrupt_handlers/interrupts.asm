bits 32

; ISR e IRQs salvando o estado do processador antes de executar qualquer outra coisa
; parametro da macro: numero da interrupção
%macro ISR_NO_DEFAULT_ERR_CODE 1 
global isr%1        ; definindo todas as ISRs que não tem código de erro padrão

isr%1:
    cli             ; desabilitar interrupções 
    push byte 0     ; valor ficticio
    push byte %1    ; push no numero da interrupção

    jmp isr_stub      
%endmacro 

; parametro da macro: numero da interrupção
%macro ISR_DEFAULT_ERR_CODE 1 
global isr%1        ; definindo todas as ISRs que tem código de erro padrão . 
isr%1:
    cli             ; desabilitar interrupções 
    
    push byte %1    ; efetuar um push no numero da interrupção

    jmp isr_stub      
%endmacro

ISR_NO_DEFAULT_ERR_CODE 0
ISR_NO_DEFAULT_ERR_CODE 1
ISR_NO_DEFAULT_ERR_CODE 2
ISR_NO_DEFAULT_ERR_CODE 3 
ISR_NO_DEFAULT_ERR_CODE 4
ISR_NO_DEFAULT_ERR_CODE 5
ISR_NO_DEFAULT_ERR_CODE 6
ISR_NO_DEFAULT_ERR_CODE 7
ISR_DEFAULT_ERR_CODE    8
ISR_NO_DEFAULT_ERR_CODE 9
ISR_DEFAULT_ERR_CODE    10
ISR_DEFAULT_ERR_CODE    11
ISR_DEFAULT_ERR_CODE    12
ISR_DEFAULT_ERR_CODE    13
ISR_DEFAULT_ERR_CODE    14
ISR_NO_DEFAULT_ERR_CODE 15
ISR_NO_DEFAULT_ERR_CODE 16
ISR_NO_DEFAULT_ERR_CODE 17
ISR_NO_DEFAULT_ERR_CODE 18
ISR_NO_DEFAULT_ERR_CODE 19
ISR_NO_DEFAULT_ERR_CODE 20
ISR_NO_DEFAULT_ERR_CODE 21
ISR_NO_DEFAULT_ERR_CODE 22
ISR_NO_DEFAULT_ERR_CODE 23
ISR_NO_DEFAULT_ERR_CODE 24
ISR_NO_DEFAULT_ERR_CODE 25
ISR_NO_DEFAULT_ERR_CODE 26
ISR_NO_DEFAULT_ERR_CODE 27
ISR_NO_DEFAULT_ERR_CODE 28
ISR_NO_DEFAULT_ERR_CODE 29
ISR_NO_DEFAULT_ERR_CODE 30
ISR_NO_DEFAULT_ERR_CODE 31


extern isr_handler 
global isr_stub

; essa seção é comum para todos as interrupções, salvamos o estado do processador antes de saltar para 
; o código da interrupção a qual vamos suportar  
isr_stub: 
	pusha           ; efetuando push em: edi, esi, ebp, esp, ebx, edx, ecx, eax 
	mov ax , ds     ; salvando o descritor de segmento de dados no stack 
	push eax 
	
	; suponha que o processador esta executando algum código de user space quando a interrupção ocorre, 
	; primeiro precisamos carregar o descritor de segmento de dados do kernel 
	mov ax, 0x10  
	mov ds, ax 
	mov es, ax
   	mov fs, ax
  	mov gs, ax 

	call isr_handler ; suportando a interrupção

	; restaurando os valores
	pop eax
	mov ds, ax 
	mov es, ax
   	mov fs, ax
   	mov gs, ax
	
	popa ; efetuando pop em: edi, esi, ebp, esp, ebx, edx, ecx, eax 
	
	; todos os ISRs farão um JMP antes de entrar no isr_stub, então, precisamos redefinir
    ; o stack antes da chamada para ISRs, (enviamos o código de erro e numero da interrupção)
    
    ; mesmo se empurrarmos apenas um byte, o ponteiro da pilha se moverá (32 bits), é daí que vem o 8 (8 bytes)
	add esp , 8
	sti              ; habilitando interrupções
	
	iret


extern irq_handler 
global irq_stub

; essa seção é comum para todos as interrupções, salvamos o estado do processador antes de saltar para 
; o código da interrupção a qual vamos suportar  	
irq_stub: 
	pusha           ; efetuando push em: edi, esi, ebp, esp, ebx, edx, ecx, eax 
	mov ax , ds     ; salvando o descritor de segmento de dados no stack
	push eax 
	
	; suponha que o processador esta executando algum código de user space quando a interrupção ocorre, 
	; primeiro precisamos carregar o descritor de segmento de dados do kernel
	mov ax, 0x10  
	mov ds, ax 
	mov es, ax
   	mov fs, ax
  	mov gs, ax 

	call irq_handler ; suportando a interrupção

    ; restaurando os valores
	pop eax
	mov ds, ax 
	mov es, ax
   	mov fs, ax
   	mov gs, ax
	
	popa ; efetuando pop em: edi, esi, ebp, esp, ebx, edx, ecx, eax 
	
	; todos os ISRs farão um JMP antes de entrar no isr_stub, então, precisamos redefinir
    ; o stack antes da chamada para ISRs, (enviamos o código de erro e numero da interrupção)

    ; mesmo se empurrarmos apenas um byte, o ponteiro da pilha se moverá (32 bits), é daí que vem o 8 (8 bytes)
	add esp , 8
	sti ; habilitando interrupões
	
	iret

; parametros da macro: porta | valor
%macro send_command_to_PIC 2  
	mov dx , %1
	mov al , %2 
	out dx ,al 
%endmacro

%define PIC1		    0x20
%define PIC2		    0xa0
%define PIC1_DATA 	    0x21
%define PIC2_DATA	    0xa1

global remap_irq
remap_irq:
	; inicailizando os 2 chips (master e slave)
    send_command_to_PIC PIC1, 0x11 
	send_command_to_PIC PIC2, 0x11 

	; mandando os novos offsets
	send_command_to_PIC PIC1_DATA, 0x20 ; = 32
	send_command_to_PIC PIC2_DATA, 0x28

    ; notificar o PIC master que existe um slave em IRQ2
	send_command_to_PIC PIC1_DATA, 0x4

	; informar a identidade da cascata do slave sendo = 2 
	send_command_to_PIC PIC2_DATA, 0x2

	; habilitando todas as interrupções ao definir a mascara como 0x00
    ; e mandando os valores padrões essperados pelos chips 
	send_command_to_PIC PIC1_DATA, 0x1
	send_command_to_PIC PIC2_DATA, 0x1
	send_command_to_PIC PIC1_DATA, 0x00
    send_command_to_PIC PIC2_DATA, 0x00
	
	ret

; parametros da macro: numero da irq e numero da interrupção
%macro IRQ 2 
global irq%1
irq%1:
    cli             ; desabilitar interrupções 
    push byte 0 
    push byte %2    ; numero da interrupção
    jmp irq_stub
%endmacro

IRQ 0, 32
IRQ 1, 33  
IRQ 2, 34  
IRQ 3, 35  
IRQ 4, 36  
IRQ 5, 37  
IRQ 6, 38  
IRQ 7, 39 
IRQ 8, 40  
IRQ 9, 41  
IRQ 10, 42  
IRQ 11, 43  
IRQ 12, 44  
IRQ 13, 45  
IRQ 14, 46
IRQ 15, 47

global EOI 
; end of interrupt (comando de fim da interrupção)
EOI:
	mov eax, [esp + 4]          ; port 
	send_command_to_PIC 0x20, al 
	ret 
