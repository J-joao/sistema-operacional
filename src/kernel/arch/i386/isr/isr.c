#include "../../../../inc/debug/logs/logs.h"
#include "../../../../kernel/panic/panic.h"
#include "isr.h"

// depois de instalar um ISR para uma determinada interrupção ou IRQ, 
// o instalador deve chamar map_handler_interrupt
isr handlers[256] = {0}; 

// essa função precisa estar aqui por causa da variavel "handlers"
void irq_handler(registers reg) {
    log_info("IRQ HANDLER CALLED\n"); 
    // mandar o final do sinal da interrupção para os PICs
    // checando se a interupção envolve o slave

    // porta 0xa0 para slave
    if(reg.int_no >= 40) { 
        EOI(0xa0); 
    }

	// mandando o fim da interrupção para master
	EOI(0x20); // porta 0x20 para master
	
    // checando se a interrupção foi instalada, se sim, chamar seu handler
	if (handlers[reg.int_no]!=0) { 
        handlers[reg.int_no](reg); 
    } 

    return; 
}

void map_handler_interrupt(unsigned int interrupt_number, isr handler) {
    // mapeando os numeros das interrupções para os handlers convenientes 
	handlers[interrupt_number] = handler;
}

void isr_handler(registers reg) {
    // escrever o numero da interrupção nos logs
    if (reg.int_no == 0) {
        log_info("reg.int_no = 0\n");
    }
    else {
        log_info("reg.int_no = %d\n", reg.int_no);
    }
    
    // suportar a interrupção de acordo com o seu valor
    switch (reg.int_no) {
        case 0:
            panic("division by zero");
            break;
        
        case 1:
            asm("sti\n\t");
            break;
        
        default:
            break;
    }

    // aqui as rotinas de serviço das interupções, exeções da CPU e faults devem ser suportadas
    return; 
}