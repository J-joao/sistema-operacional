#ifndef ISR_H
#define ISR_H

// essa struct é baseada em como o irs_stub vai "pushar" dados no stack
typedef struct registers_struct {
   unsigned int ds;                                     // seletor de segmento de dados
   unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; // "pushados" pela instrução pusha
   unsigned int int_no, err_code;    
   unsigned int eip, cs, eflags, useresp, ss;           // "pushados" pelo processador automaticamente
} registers;

// fim da interrupção (end of interrupt) 
extern void EOI();

// handlers 
typedef void (*isr)(registers); 

// chame essa função para mapear uma interrupção assim que instalada
void map_handler_interrupt(unsigned int interrupt_number, isr handler);

#endif //ISR_H