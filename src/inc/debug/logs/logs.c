#include <stdarg.h>

#include "../../useful/useful.h"
#include "../../string.h"
#include "../../IO/io.h"
#include "logs.h"

void log_putchar(char c) {
    outportb(0xe9, c);
}

void log_write_str(const char *str) {
    int len = (int) strlen(str);
    
    // escrever a string 1 caracter por vez no arquivo de log
    for (int i = 0; i < len; i++) {
        log_putchar(str[i]);
    }
}

void log_write_formated_str(char *format, ...) {
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
                    // escrever a string formatada no arquivo de log que for passada como argumento
                    log_write_str(va_arg(ap, char *));
                    break;
                // caso seja encontrado "%d"
                case 'd':
                    // escrever o numero decimal em forma de string no arquivo de log
                    log_write_str(itoa(va_arg(ap, int), 10));
                    break;
                // caso seja encontrado "%x"
                case 'x':
                    // escrever o numero hexadecimal em forma de string no arquivo de log
                    log_write_str(itoa(va_arg(ap, int), 16));
                    break;
                // caso seja encontrado "%b"
                case 'b':
                    // escrever o numero binario em forma de string no arquivo de log
                    log_write_str(itoa(va_arg(ap, int), 2));
                    break;
            }
        } 
        // se não for encontrado "%", escrever a string no arquivo de log que for passada como argumento
        else { log_putchar(*ptr++); }
    }
    va_end(ap);
}
