/**
 * SurgeOS kernel idt.c
 * Interrupt Descriptor Table (IDT) implementation
 */

#include <kernel/kernel.h>
#include <stdint.h>
#include <stdbool.h>
#include <kernel/isr.h>

extern void isr_default(void);
extern void isr_load(idt_ptr_t* idt_ptr);
extern void pic_remap(void);

static idt_entry_t idt_entries[256];
static idt_ptr_t idt_ptr;

void set_idt_entry(int index, uint32_t base, uint16_t selector, uint8_t type_attr) {
  idt_entries[index].base_low = (uint16_t)(base & 0xFFFF);
  idt_entries[index].selector = selector;
  idt_entries[index].always0 = 0;
  idt_entries[index].type_attr = type_attr;
  idt_entries[index].base_high = (uint16_t)((base >> 16) & 0xFFFF);
}

void init_idt() {
  idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
  idt_ptr.base = (uint32_t)&idt_entries;

  // Initialize IDT entries
  for (int i = 0; i < 256; i++) {
    set_idt_entry(i, (uint32_t)isr_default, 0x08, 0x8E); // Present, DPL=0, 32-bit interrupt gate
  }

  // Setting specific interrupt handlers
  set_idt_entry(0x21, (uint32_t)isr_keyboard, 0x08, 0x8E); // IRQ1 (keyboard)

  set_idt_entry(0x80, (uint32_t)isr_syscall, 0x08, 0x8E); // Syscall handler

  isr_load(&idt_ptr);
  pic_remap(); // Remap the PIC
  asm volatile("sti"); // Enable interrupts
}

