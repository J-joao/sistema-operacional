#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

// largura = 80
#define VGA_WIDTH 80
// altura = 25
#define VGA_HEIGHT 25

// definir o tamanho padrão do tab (aqui no caso, são 4 espaços em branco)
#define DEFAULT_TAB_WIDTH 4

// ponteiro da memoria de video (ou, buffer linear de texto), primeiramente definido como 0
static uint16_t *text_buffer = 0;

// cores dos bytes de atributo
enum vga_colors {
	VGA_COL_BLACK, VGA_COL_BLUE, VGA_COL_GREEN, VGA_COL_CYAN,
	VGA_COL_RED, VGA_COL_MAGENTA, VGA_COL_BROWN, VGA_COL_LIGHT_GREY,
	VGA_COL_DARK_GREY, VGA_COL_LIGHT_BLUE, VGA_COL_LIGHT_GREEN, VGA_COL_LIGHT_CYAN,
	VGA_COL_LIGHT_RED, VGA_COL_LIGHT_MAGENTA, VGA_COL_LIGHT_BROWN, VGA_COL_WHITE
};
#define DEFAULT_COL VGA_COL_BLACK, VGA_COL_WHITE

// funções para o reconhecimento de caracteres de scape (\n, \t, \r...)
void vga_newline(void);
void vga_tab(void);
void vga_carriage_return(void);

// essa função indica o endereço do buffer de texto, zera as coordenadas (x, y) e limpa a tela
void vga_initialize(void);

// essa função formata um caracter com base em seu byte de atributo e valor ASCII, 
// devolvendo um valor 16 bits que pode ser escrito no buffer de texto 
uint16_t format_character(const uint8_t bg, const uint8_t fg, char c);

// essa função limpa o buffer de texto
void vga_clear_screen(void);

// essa função escreve um caracter, com base nas coordenadas (x, y), no buffer de texto
void vga_putchar_xy(const uint8_t bg, const uint8_t fg, int x, int y, char c);

// essa função escreve um caracter, com base nas coordenadas atuais, no buffer de texto
void vga_putchar(const uint8_t bg, const uint8_t fg, char c);

// essa função escreve uma string literal, com base nas coordenadas atuais, no buffer de texto
void vga_write_str(const uint8_t bg, const uint8_t fg, const char *str);

// essa função escreve uma string formatada, com base nas coordenadas atuais, no buffer de texto
void vga_write_formated_str(const uint8_t bg, const uint8_t fg, char *format, ...);

#endif //VGA_H