#ifndef STRING_H
#define STRING_H

#include <stddef.h>

/// determina o tamanho de uma string excluindo seu caracter finalizador = tamanho da string
// @param str = string a ser contada
size_t strlen(const char *str); 

/// concatena 2 strings
// @param dest = string de destino
// @param src = string a ser concatenada em "dest"
char *strcat(char *dest, const char *src); 

#endif //STRING_H