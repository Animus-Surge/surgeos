/**
 * SurgeOS kernel isr.c
 * Interrupt Service Routines (ISRs) implementation
 */

#include <kernel/kernel.h>
#include <kernel/isr.h>
#include <kernel/keyboard.h>

#include <stdio.h>
#include <stdint.h>

void isr_keyboard_input(uint32_t scancode) {
  char ascii = get_ascii_from_scancode(scancode);
  if (ascii) {
    printf("%c", ascii);
  }
}

void isr_syscall_handler(uint32_t syscall) {
}
