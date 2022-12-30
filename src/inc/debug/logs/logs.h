#ifndef LOGS_H
#define LOGS_H

#include <stdarg.h>

// essas funções usam de uma caracteristica do qemu, na qual, quando algo é 
// escrito na porta 0xe9, essa porta pode ser usada para trasnmitir valores 
// para fora da maquina virtual. usaremos disso para escrever no arquivo
// kernel_logs.log

enum log_modes {
    LOG_INFO, LOG_WARN, LOG_ERR, LOG_CRIT
};

// essa função escreve um caracter na porta 0xe9
void log_putchar(char c);

// essa função escreve uma string na porta 0xe9
void log_write_str(const char *str);

// essa função escreve uma string formatada na porta 0xe9
void log_write_formated_str(char *format, ...);

#define log_info(MSG,ARGS...) log_write_formated_str("[INFO] #%s: " MSG,__func__,##ARGS)
#define log_warn(MSG,ARGS...) log_write_formated_str("[WARNING] #%s: " MSG,__func__,##ARGS)
#define log_err(MSG,ARGS...) log_write_formated_str("[ERROR] #%s: " MSG,__func__,##ARGS)
#define log_crit(MSG,ARGS...) log_write_formated_str("[CRITICAL] #%s: " MSG,__func__,##ARGS)

#endif //LOGS_H