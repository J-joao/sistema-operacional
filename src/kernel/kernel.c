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
#include  "../inc/vga/vga.h"
#include "../inc/debug/logs/logs.h"
#include "kernel.h"

void kernel_main() {
    vga_initialize();

    vga_write_formated_str(DEFAULT_COL, "\tolo\ra %s", "mundo\n");
    vga_write_formated_str(VGA_COL_WHITE, VGA_COL_BLACK, "decimal: %d\n", 200 + 56);    
    vga_write_formated_str(VGA_COL_WHITE, VGA_COL_BLACK, "hex:     %x\n", 200 + 56);
    vga_write_formated_str(VGA_COL_WHITE, VGA_COL_BLACK, "bin:     %b\n", 200 + 56);

    #define E9_PORT_HACK
    #ifdef E9_PORT_HACK
        log_info("teste %s %s %s %s %d\n", "de", "log", "com", "argumentos", 3300 + 1);
        log_warn("teste %s %s %s %s %d\n", "de", "log", "com", "argumentos", 3300 + 1);
        log_err("teste %s %s %s %s %d\n", "de", "log", "com", "argumentos", 3300 + 1);
        log_crit("teste %s %s %s %s %d\n", "de", "log", "com", "argumentos", 3300 + 1);
    #endif
}
