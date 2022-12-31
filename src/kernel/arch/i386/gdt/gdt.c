#include "gdt.h"

extern void gdt_flush(int) ;

// segmento de dados e código para o kernel, segmento da dados e código para user mode, entrada nula  
gdt_entry gdt_entries[5]; 

gdt_ptr GDT;

static void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran) { 
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

void init_gdt() {
    GDT.limit = sizeof(gdt_entry) * 5 - 1;
    GDT.base  = (int)&gdt_entries;

    gdt_set_entry(0, 0, 0, 0, 0);                // segmento nulo
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // segmento de código do kernel
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // segmento de dados do kernel
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // segmento de código do user mode
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // segmento de dados do user mode

    gdt_flush((int)&GDT);
}