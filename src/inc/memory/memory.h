#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

// essa função define os primeiros bytes (de acordo com o tamanho "size") de "dest" para o valor "c"
void *memset(void *ptr, int c, size_t size);

#endif //MEMORY_H