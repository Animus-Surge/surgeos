/**
 * SurgeOS kernel/kernel.h
 * Kernel header file
 */

#ifndef SURGEOS_KERNEL_KERNEL_H
#define SURGEOS_KERNEL_KERNEL_H

#include <stdint.h>

typedef struct {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;
  uint8_t granularity;
  uint8_t base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

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

#ifdef __cplusplus
extern "C" {
#endif

// Descriptor tables
extern void _gdt_load(gdt_ptr_t* gdt_ptr);
extern void _idt_load(idt_ptr_t* idt_ptr);

extern void isr_default(void);

void init_gdt(void);
void init_idt(void);

#ifdef __cplusplus
}
#endif

#endif // SURGEOS_KERNEL_KERNEL_H
