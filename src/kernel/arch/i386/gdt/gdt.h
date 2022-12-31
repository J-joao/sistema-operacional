#ifndef GDT_H
#define GDT_H

struct gdt_entry_struct {
    unsigned short limit_low;          // 16 bits inferiores dao limite
    unsigned short base_low;           // 16 bits inferiores da base
    unsigned char base_middle;         // proximos 8 bits da base
    unsigned char access;              // flags de acesso,determina o nivel de privilegio do segmento 
    unsigned char granularity;
    unsigned char base_high;           // ultimos 8 bits da base
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry;

struct gdt_ptr_struct {
    unsigned short limit;             
    unsigned int base;                 // endereço da primeira entrada GDT
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr;

// iniciar GDT
void init_gdt();

// definir valor de uma entrada GDT 
static void gdt_set_entry(int,unsigned int,unsigned int,unsigned char,unsigned char);

#endif //GDT_H