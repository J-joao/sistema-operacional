#ifndef LOGS_H
#define LOGS_H

#include <stdarg.h>

// essas funções usam de uma caracteristica do qemu, na qual, quando algo é 
// escrito na porta 0xe9, essa porta pode ser usada para trasnmitir valores 
// para fora da maquina virtual. usaremos disso para escrever no arquivo
// kernel_logs.log

// escreve um caracter na porta 0xe9
// @param c = caracter a ser escrito
void log_putchar(char c);

// escreve uma string na porta 0xe9
// @param str = string a ser escrita
void log_write_str(const char *str);

// escreve uma string formatada na porta 0xe9
// @param format = string formatada a ser escrita
void log_write_formated_str(char *format, ...);

#define E9_PORT_HACK

#ifdef E9_PORT_HACK
    #define log_info(MSG,ARGS...) log_write_formated_str("[INFO] #%s: " MSG,__func__,##ARGS)
    #define log_warn(MSG,ARGS...) log_write_formated_str("[WARNING] #%s: " MSG,__func__,##ARGS)
    #define log_err(MSG,ARGS...) log_write_formated_str("[ERROR] #%s: " MSG,__func__,##ARGS)
    #define log_crit(MSG,ARGS...) log_write_formated_str("[CRITICAL] #%s: " MSG,__func__,##ARGS)
#else 
    #define log_info(MSG,ARGS...)
    #define log_warn(MSG,ARGS...)
    #define log_err(MSG,ARGS...) 
    #define log_crit(MSG,ARGS...)
#endif

#endif //LOGS_H