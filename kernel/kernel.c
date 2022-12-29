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
#include "../inc/vga.h"
#include "kernel.h"

#define DEBUG
#ifdef DEBUG
    #define vga_debug_msg(COLOR, MSG, ARGS...) \
    vga_write_formated_str(COLOR, "[DEBUG]: %s: " MSG, __func__, ##ARGS)
#else
    #define vga_debug_msg(MSG,ARGS...)
#endif

void kernel_main() {
    // indicar o endereço do ponteiro da memória de video e limpar a tela
    vga_initialize();

    vga_write_str(VGA_COLOR_WHITE, "ola mundo!\n\ttestando\n");
    vga_write_formated_str(VGA_COLOR_BLUE, "ola %s", "mundo\n");
    vga_debug_msg(VGA_COLOR_LIGHT_GREEN, "debug aqui caralho, testando essa bosta\n");
}
