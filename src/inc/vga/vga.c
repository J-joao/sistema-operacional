#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "../string.h"
#include "../useful/useful.h"
#include "vga.h"

// posição da linha do terminal vga
uint16_t vga_row = 0;
// posição da coluna do terminal vga
uint16_t vga_col = 0;

void vga_newline(void) {
    vga_row++;
    vga_col = 0;
}
void vga_tab(void) {
    vga_col += DEFAULT_TAB_WIDTH;
}
void vga_carriage_return(void) {
    vga_col--;
}

void vga_initialize(void) {
    // no modo VGA 3, o endereço físico para o buffer de texto é 0xb8000
    text_buffer = (uint16_t *)(0xb8000);
    vga_row = 0;
    vga_col = 0;   
    vga_clear_screen();
}

uint16_t format_character(const uint8_t bg, const uint8_t fg, char c) {
    uint16_t attr_byte = (bg << 4) | (fg & 0x0f);
    return c | (attr_byte << 8);
}

void vga_clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            // text_buffer[x, y] = espaço em branco
            vga_putchar_xy(VGA_COL_BLACK, VGA_COL_BLACK, x, y, ' ');
        }
    }
}

void vga_putchar_xy(const uint8_t bg, const uint8_t fg, int x, int y, char c) {
    text_buffer[(y * VGA_WIDTH) + x] = format_character(bg, fg, c);
}

void vga_putchar(const uint8_t bg, const uint8_t fg, char c) {
    if (c == '\n') {
        vga_newline();
        return;
    }
    if (c == '\t') {
        vga_tab();
        return;
    }
    if (c == '\r') {
        vga_carriage_return();
        return;
    }

    // escrever caracter na posição atual do cursor
    vga_putchar_xy(bg, fg, vga_col, vga_row, c);
    // incrementar a posição horizontal
    vga_col++;

    // se ultrapassarmos os limites horizontais, quebra de linha
    if (vga_col >= VGA_WIDTH) {
        vga_newline();
    }
}

void vga_write_str(const uint8_t bg, const uint8_t fg, const char *str) {
    int len = (int) strlen(str);
    
    // escrever a string 1 caracter por vez
    for (int i = 0; i < len; i++) {
        vga_putchar(bg, fg, str[i]);
    }
}

void vga_write_formated_str(const uint8_t bg, const uint8_t fg, char *format, ...) {
    // declarar e iniciar lista de argumentos
    va_list ap;
    va_start(ap, format);

    // ponteiro para a string passada
    char *ptr = format;

    while(*ptr) {
        // caso seja encontrado "%":
        if (*ptr == '%') {
            ptr++;

            switch (*ptr++) {
                // caso seja encontrado "%s"
                case 's':
                    // escrever a string formatada que for passada como argumento
                    vga_write_str(bg, fg, va_arg(ap, char *));
                    break;
                // caso seja encontrado "%d"
                case 'd':
                    // escrever o numero decimal em forma de string
                    vga_write_str(bg, fg, itoa(va_arg(ap, int), 10));
                    break;
                // caso seja encontrado "%x"
                case 'x':
                    // escrever o numero hexadecimal em forma de string
                    vga_write_str(bg, fg, itoa(va_arg(ap, int), 16));
                    break;
                // caso seja encontrado "%b"
                case 'b':
                    // escrever o numero binario em forma de string
                    vga_write_str(bg, fg, itoa(va_arg(ap, int), 2));
                    break;
            }
        } 
        // se não for encontrado "%", escrever a string que for passada como argumento
        else { vga_putchar(bg, fg, *ptr++); }
    }
    va_end(ap);
}