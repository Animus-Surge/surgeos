/**
 * SurgeOS kernel/kernel.h
 * Kernel header file
 */

#ifndef SURGEOS_KERNEL_KERNEL_H
#define SURGEOS_KERNEL_KERNEL_H

#include <sys/cdefs.h>

#include <stdint.h>

__EXTC

typedef struct {
  uint16_t base_low;
  uint16_t selector;
  uint8_t always0;
  uint8_t type_attr;
  uint16_t base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_ptr_t;

extern void isr_default(void);

void init_gdt(void);
void init_idt(void);

__EXTC_END

#endif // SURGEOS_KERNEL_KERNEL_H
