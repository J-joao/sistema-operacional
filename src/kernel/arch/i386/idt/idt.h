#ifndef IDT_H 
#define IDT_H

#include <stddef.h>
#include <stdint.h>

struct idt_entry_struct {
    uint16_t base_lo;            // 16 bits inferiores da base
    uint16_t selector;           // seletor de segmento do kernel
    uint8_t zero;                // sempre zero
    uint8_t flags;               // nivel de privilegio
    uint16_t base_hi;            // 16 bits superiores
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry;

struct idt_desc_struct {
    uint16_t limit;              // valor limite
    uint32_t base;                 // endereço da primeira entrada IDT
} __attribute__((packed));

typedef struct idt_desc_struct idt_desc;

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

/// iniciar IDT
void init_idt(void);

/// remapeia as IRQs
extern void remap_irq(void); 

/// carrega a IDT
extern void idt_set(uint32_t);

/// define o valor de uma entrada IDT
// @param num = index na IDT
// @param base = valor da base
// @param sel = seletor do kernel
// @param flags = nivel de privilegio
static void idt_set_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags); 

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

#endif //IDT_H