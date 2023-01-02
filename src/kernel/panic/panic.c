#include "../../kernel/arch/i386/interrupt_handlers/isr.h"
#include "../../inc/debug/logs/logs.h"
#include "../../inc/vga/vga.h"
#include "panic.h"

void panic(const char *str) {
    // fazer o log dizendo que houve um kernel panic e a razão deste
    log_crit("a kernel panic has occured | reason: %s\n", str);

    vga_write_str(VGA_COL_BLACK, VGA_COL_RED, KERNEL_PANIC_DEFAULT_MSG);
    vga_write_formated_str(DEFAULT_COL, "reason: %s\n", str);

    
    for(;;) { asm("hlt\n\t"); }
}
