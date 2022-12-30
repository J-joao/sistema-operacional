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
    log_info("initializing linear text-buffer\n");
    vga_initialize();

    vga_write_formated_str(VGA_COL_WHITE, VGA_COL_BLACK, "bem vindo ao "OS_NAME);
}
