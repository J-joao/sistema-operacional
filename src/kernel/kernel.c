// #if defined(__linux__)
//     #error "voce nao esta usando um compilador cruzado (cross-compiler)"
// #endif
 
// #if !defined(__i386__)
//     #error "esse codigo deve ser compilado com um compilador ix86-elf"
// #endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../inc/string.h"
#include "../inc/vga/vga.h"
#include "../inc/debug/logs/logs.h"
#include "./arch/i386/gdt/gdt.h"
#include "./arch/i386/idt/idt.h"
#include "./arch/i386/interrupt_handlers/isr.h"
#include "./drivers/keyboard/kb.h"
#include "kernel.h"

#define vga_printf(MSG, ARGS...) vga_write_formated_str(DEFAULT_COL, MSG, ##ARGS)

void kernel_entry(void) {
    /*----------------- preparativos antes de inicializar o kernel -----------------*/
    // inicializando o buffer de texto linar (modo vga)
    log_info("initializing linear text-buffer\n");
    // no modo VGA 3, o endereço físico para o buffer de texto é 0xb8000
    vga_initialize(0xb8000);

    // inicializando e configurando a GDT
    log_info("initializing GDT\n");
    init_gdt();
    
    // inicializando e configurando a IDT
    log_info("initializing IDT\n");
    init_idt();

    // habilitando o kernel a receber interrupções
    log_info("calling \"sti\" instruction (to receive interrupts)\n");
    __asm__ __volatile__("sti\n\t");
    
    // mapear o handler do int $33 (teclado)
    log_info("maping interrupt number 33\n");
    map_interrupt_handler(33, keyboard_handler);

    /*----------------- inicializando o kernel -------------------------------------*/
    vga_write_str(VGA_COL_WHITE, VGA_COL_BLACK, ">>>> https://github.com/J-joao/\n\n");
    
    // isso causa um kernel panic
    // __asm__ __volatile__("int $0\n\t");

    // chamando a interrupção int $33 (iniciando o driver de teclado)
    log_info("calling int $33\n");
    __asm__ __volatile__("int $33\n\t");

    // loop infinito
    for(;;) { __asm__ __volatile__("hlt\n\t"); }
}
