#ifndef ISR_H
#define ISR_H

#include <stddef.h>
#include <stdint.h>

typedef struct registers_struct {
   uint32_t ds;                                     // seletor de segmento de dados
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // empurrados no stack pela instrução "pusha"
   uint32_t int_no, err_code;                       // numero da interrupção e código de erro    
   uint32_t eip, cs, eflags, useresp, ss;           // automaticamente empurrados pelo processador no stack
} registers;

/// fim da interrupção (end of interrupt) (definida em assembly) 
extern void EOI();

/// handlers 
typedef void (*isr)(registers); 

/// mapeia uma interrupção
// @param interrupt_number = numero da interrupção
// @param handler = função manipuladora da interrupção
void map_interrupt_handler(uint32_t interrupt_number, isr handler);

/// manipula uma interrupção 
// @param reg = estrutura contendo os valores dos registradores do sistema 
void isr_handler(registers reg);

/// manipula uma requisição de instrução e manda o final do sinal da interrupção para os PICs
// @param reg = estrutura contendo os valores dos registradores do sistema
void irq_handler(registers reg);

#endif //ISR_H