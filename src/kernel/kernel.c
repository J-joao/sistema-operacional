#if defined(__linux__)
    #error "voce nao esta usando um compilador cruzado (cross-compiler)"
#endif
 
#if !defined(__i386__)
    #error "esse codigo deve ser compilado com um compilador ix86-elf"
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "../inc/string.h"
#include "../inc/vga/vga.h"
#include "../inc/debug/logs/logs.h"
#include "./arch/i386/gdt/gdt.h"
#include "./arch/i386/idt/idt.h"
#include "./arch/i386/isr/isr.h"
#include "kernel.h"

void kernel_entry() {
    log_info("initializing linear text-buffer\n");
    vga_initialize();

    log_info("initializing GDT\n");
    init_gdt();
    log_info("initializing IDT\n");
    init_idt();

    vga_write_str(VGA_COL_WHITE, VGA_COL_BLACK, "                     "
                                                "welcome to "OS_NAME
                                                "                   \n\n");

    vga_write_formated_str(DEFAULT_COL, "calling int $1:\n");
    asm("int $1\n\t");

    vga_write_formated_str(DEFAULT_COL, "calling int $0:\n");
    asm("int $0\n\t");

    for(;;) { asm("hlt"); }
}
