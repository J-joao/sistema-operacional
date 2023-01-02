#include "../../../../inc/debug/logs/logs.h"
#include "../../../../kernel/panic/panic.h"
#include "isr.h"

// depois de instalar um ISR para uma determinada interrupção ou IRQ, o instalador deve chamar map_interrupt_handler
isr handlers[256] = {0}; 

void irq_handler(registers reg) {
    // checando se a interupção envolve o slav
    // porta 0xa0 para slave
    if(reg.int_no >= 40) { 
        EOI(0xa0); 
    }

	// mandando o fim da interrupção para master
	EOI(0x20); // porta 0x20 para master
	
    // checando se a interrupção foi instalada, se sim, chamar seu handler
	if (handlers[reg.int_no] != 0) { 
        handlers[reg.int_no](reg); 
    }

    return; 
}

void map_interrupt_handler(uint32_t interrupt_number, isr handler) {
    // mapeando os numeros das interrupções para os handlers convenientes 
	handlers[interrupt_number] = handler;
}

void isr_handler(registers reg) {
    // escrever o numero da interrupção nos logs
    log_info("reg.int_no = %d\n", reg.int_no);
    
    
    // manipular a interrupção de acordo com o numero (reg.int_no)
    switch (reg.int_no) {
        case 0:
            panic("divide-by-zero error");
            break;
        
        case 1:
            break;
        
        default:
            break;
    }

    // habilitar interupções (para evitar ficar preso em um loop)
    __asm__ __volatile__ ("sti\n\t");

    return; 
}