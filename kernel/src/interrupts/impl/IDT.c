#include <interrupts/IDT.h>
#include <interrupts/exceptions.h>

static idt_vector_t idt[256];
static idtr_t idtr;

void idt_set_vector(uint8_t vector, void* isr) {
    uint64_t addr = (uint64_t)isr;
    idt[vector].isr_low = addr & 0xFFFF;
    idt[vector].isr_mid = (addr & 0xFFFF0000) >> 16;
    idt[vector].isr_high = (addr & 0xFFFFFFFF00000000) >> 32;
    idt[vector].dpl = 0;
    idt[vector].p = 1;
    idt[vector].attr = 0xF;
    idt[vector].cs = 0x28;
    idt[vector].reserved = 0x0;
    idt[vector].reserved2 = 0x0;
}


void idt_install() {  
    idtr.limit = sizeof(idt_vector_t) * 255;
    idtr.base = (uint64_t)&idt; 
    __asm__ __volatile__("lidt %0" : : "memory" (idtr));
}
