#ifndef __XOS_IDT_H__
#define __XOS_IDT_H__

#define TRAP_GATE_FLAGS 0x8F
#define INT_GATE_FLAGS 0x8E

#include <stdint.h>

/*
 *  The interrupt descriptor table is 
 *  a table used to tell the CPU how
 *  to respond to an interrupt or 
 *  exception. Each IDT entry will
 *  hold the bits of an ISR (Interrupt Service Routine).
 *  An interrupt service routine gets executed by the CPU 
 *  during an interrupt/exception.
 */


// This is an IDT entry, also known as a vector.
typedef struct {
    uint16_t isr_low;           // Low bits of ISR.
    uint16_t cs;                // Code segment to load into CS before calling ISR.
    uint8_t ist : 3;            // Interrupt stack table/
    uint8_t reserved : 5; 
    uint8_t attr : 4;           // ISR attributes.
    uint8_t reserved1 : 1;
    uint8_t dpl : 2;            // Descriptor priv level.
    uint8_t p : 1;              // Present.
    uint16_t isr_mid;           // Middle bits of ISR.
    uint32_t isr_high;          // High bits of ISR.
    uint32_t reserved2;
} __attribute__((packed)) idt_vector_t;


// This structure will tell the CPU where the IDT is.
typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idtr_t;


// This is the IDTR it will get pushed to the stack
// during an interrupt to give information about
// the CPU state.
typedef struct {
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
} __attribute__((packed)) int_frame_t;


void idt_install();
void idt_set_vector(uint8_t vector, void* isr);

#endif
