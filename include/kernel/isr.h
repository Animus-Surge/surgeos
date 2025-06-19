/**
 * SurgeOS kernel isr.h
 * Interrupt Service Routines (ISRs) header file
 */

#ifndef SURGEOS_KERNEL_ISR_H
#define SURGEOS_KERNEL_ISR_H

#include <stdint.h>

// Default handler
extern void isr_default(void);

// IRQ handlers

extern void isr_keyboard(void); // 0x21
void isr_keyboard_input(uint32_t);

extern void isr_page_fault(void); // 0x0E
void isr_page_fault_handler(uint32_t, uint32_t);

#endif // SURGEOS_KERNEL_ISR_H
