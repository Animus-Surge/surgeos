/**
 * SurgeOS kernel isr.h
 * Interrupt Service Routines (ISRs) header file
 */

#ifndef SURGEOS_KERNEL_ISR_H
#define SURGEOS_KERNEL_ISR_H

#include <stdint.h>

typedef struct {
  uint32_t ds;        // Data segment selector
  uint32_t edi;      // Destination index register
  uint32_t esi;      // Source index register
  uint32_t ebp;      // Base pointer register
  uint32_t esp;      // Stack pointer register
  uint32_t ebx;      // Base register
  uint32_t edx;      // Data register
  uint32_t ecx;      // Counter register
  uint32_t eax;      // Accumulator register
} __attribute__((packed)) isr_regs_t;

// Default handler
extern void isr_default(void);

// IRQ handlers

extern void isr_keyboard(void); // 0x21
void isr_keyboard_input(uint32_t);

extern void isr_syscall(void); // 0x80
void isr_syscall_handler(isr_regs_t*);


#endif // SURGEOS_KERNEL_ISR_H
