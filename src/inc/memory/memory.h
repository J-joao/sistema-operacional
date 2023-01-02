#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

/// define os primeiros bytes de "ptr" para o valor "c" = ponteiro "ptr"
// @param ptr = ponteiro a ser modificado
// @param c = valor de substituição
// @param size = numero de bytes a serem modificados
void *memset(void *ptr, int c, size_t size);

#endif //MEMORY_H