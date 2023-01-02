#ifndef PANIC_H
#define PANIC_H

#include <stddef.h>
#include <stdint.h>

#define KERNEL_PANIC_DEFAULT_MSG "++++++++++++KERNEL PANIC++++++++++++\n"

/// função de panico do kernel (quando todas as tentativas de consertar um erro foram falhas ou quando o erro é inadimissivel)
// @param str = mensagem dizendo o motivo do kernel panic
void panic(const char *str);

#endif //PANIC_H