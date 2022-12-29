#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

// largura = 80
#define VGA_WIDTH 80
// altura = 25
#define VGA_HEIGHT 25

static uint16_t *video_mem = 0;

// cores dos bytes de atributo
enum vga_colors {
	VGA_COLOR_BLACK, VGA_COLOR_BLUE, VGA_COLOR_GREEN, VGA_COLOR_CYAN,
	VGA_COLOR_RED, VGA_COLOR_MAGENTA, VGA_COLOR_BROWN, VGA_COLOR_LIGHT_GREY,
	VGA_COLOR_DARK_GREY, VGA_COLOR_LIGHT_BLUE, VGA_COLOR_LIGHT_GREEN, VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED, VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_LIGHT_BROWN, VGA_COLOR_WHITE,
};

// essa função retorna os valores de (caracter + cor) como sendo um unico valor 16 bits
uint16_t vga_make_char(const char color, char c);
// essa função apenas quebra a linha de texto
void vga_newline();
// essa função indica o enderço da memoria de video e "limpa" o terminal vga
void vga_initialize(void);
// essa função escreve um caracter no terminal conforme a posição (X, Y) do cursor
void vga_putchar_xy(const char color, int x, int y, char c);
// essa função escreve um caracter no terminal conforme a posição atual do cursor
void vga_putchar(const char color, char c);
// essa função escreve uma string no terminal
void vga_write_str(const char color, const char *str);
// essa função escreve uma string formatada no terminal
void vga_write_formated_str(const char color, char *format, ...);

#endif //VGA_H