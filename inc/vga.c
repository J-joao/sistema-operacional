#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "string.h"
#include "vga.h"

uint16_t vga_row = 0;
uint16_t vga_col = 0;

uint16_t vga_make_char(const char color, char c) {
    return (color << 8) | c;
}

void vga_newline() {
    vga_row++;
    vga_col = 0;
    return;
}

void vga_initialize(void) {
    video_mem = (uint16_t *)(0xB8000);
    vga_row = 0;
    vga_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_putchar_xy(x, y, ' ', 0);
        }
    }   
}

void vga_putchar_xy(const char color, int x, int y, char c) {
    video_mem[(y * VGA_WIDTH) + x] = vga_make_char(color, c);
}

void vga_putchar(const char color, char c) {
    if (c == '\n') {
        vga_row++;
        vga_col = 0;
        return;
    }
    if (c == '\t') {
        vga_col += 4;
        return;
    }

    vga_putchar_xy(color, vga_col, vga_row, c);
    vga_col++;

    if (vga_col >= VGA_WIDTH) {
        vga_col = 0;
        vga_row++;
    }
}

void vga_write_str(const char color, const char *str) {
    int len = (int) strlen(str);
    
    for (int i = 0; i < len; i++) {
        vga_putchar(color, str[i]);
    }
}

void vga_write_formated_str(const char color, char *format, ...) {
    va_list ap;
    va_start(ap, format);

    char *ptr = format;

    while(*ptr) {
        if (*ptr == '%') {
            ptr++;

            switch (*ptr++) {
                case 's':
                    vga_write_str(color, va_arg(ap, char *));
                    break;
            }
        } 
        else { vga_putchar(color, *ptr++); }
    }

  va_end(ap);
}