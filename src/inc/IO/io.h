#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdint.h>

/// le o valor de uma porta = valor contido na porta
// @port = porta a ser lida
uint8_t inportb (uint16_t port);

/// escreve dados em uma porta
// @port = porta a ser escrita
// @data = dados a serem escritos na porta
void outportb (uint16_t port, uint8_t data);

#endif //IO_H