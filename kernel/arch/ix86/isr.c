/**
 * SurgeOS kernel isr.c
 * Interrupt Service Routines (ISRs) implementation
 */

#include <kernel/kernel.h>
#include <kernel/isr.h>

#include <drivers/keyboard.h>
#include <drivers/serial.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void isr_keyboard_input(uint32_t scancode) {
  char ascii = sc_to_ascii(scancode);

  serial_printf("ISR: Keyboard: scancode 0x%x, ASCII 0x%x\n", scancode, ascii);

  if (ascii) {
    serial_printf("ISR: Keyboard: added character\n");
    keyboard_addchar(ascii);
  }
}

void isr_page_fault_handler(uint32_t error_code, uint32_t faulting_address) {
  serial_printf("ISR: Page fault at address 0x%x, error code: 0x%x\n", (uintptr_t)&faulting_address, error_code);

  // Decode error code
  bool present = error_code & 0x1; // Page not present
  bool write = error_code & 0x2;   // Write operation
  bool user = error_code & 0x4;    // User mode access
  bool reserved = error_code & 0x8; // Reserved bit set
  bool instruction = error_code & 0x10; // Instruction fetch

  serial_printf("ISR: Page fault details:\n");
  serial_printf("ISR: - Present: %d\n", present);
  serial_printf("ISR: - Write: %d\n", write);
  serial_printf("ISR: - User: %d\n", user);
  serial_printf("ISR: - Reserved: %d\n", reserved);
  serial_printf("ISR: - Instruction: %d\n", instruction);

  panic("Page fault occurred. System halted.");
}

void isr_double_fault_handler(uint32_t error_code, uint32_t faulting_address) {
  // TODO: implement logic
  panic("Double fault occurred. System halted.");
}
