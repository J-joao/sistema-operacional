#ifndef STRING_H
#define STRING_H

#include <stddef.h>

// essa função determina o tamanho de uma string (excluindo seu caracter finalizador)
size_t strlen(const char *str); 
// essa função concatena 2 strings
char *strcat(char *dest, const char *src); 

#endif //STRING_H