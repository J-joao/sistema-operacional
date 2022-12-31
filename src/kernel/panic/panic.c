#include "../../inc/debug/logs/logs.h"
#include "../../inc/vga/vga.h"
#include "panic.h"

void panic(const char *str) {
    log_crit("a kernel panic has occured | reason: %s\n", str);
    vga_write_str(VGA_COL_BLACK, VGA_COL_RED, "++++++++++++KERNEL PANIC++++++++++++\n");
    vga_write_formated_str(DEFAULT_COL, "reason: %s", str);
    
    for(;;) { asm("hlt\n\t"); }
}
