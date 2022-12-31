#ifndef IDT_H 
#define IDT_H

struct idt_entry_struct {
    unsigned short base_lo;            // 16 bits inferiores da base
    unsigned short selector;           // seletor de segmento do kernel
    unsigned char zero;                // sempre zero
    unsigned char flags;               
    unsigned short base_hi;            // 16 bits superiores
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry;

struct idt_desc_struct {
    unsigned short limit;
    unsigned int base;                 // endereço da primeira entrada IDT
} __attribute__((packed));

typedef struct idt_desc_struct idt_desc;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// iniciar IDT
void init_idt();

extern void remap_irq(); 

extern void idt_flush(unsigned int);

// definir valor de uma entrada IDT 
static void idt_set_entry(unsigned char num, unsigned int  base, unsigned short sel, unsigned char flags); 

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif //IDT_H