#include "io.h"

uint8_t inportb (uint16_t port) {
    uint8_t return_val;
    
    // input: return val
    // output: port
    __asm__ __volatile__ ("inb %1, %0" : "=a" (return_val) : "dN" (port));
    return return_val;
}

void outportb (uint16_t port, uint8_t data) {
    // output: port, data
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
