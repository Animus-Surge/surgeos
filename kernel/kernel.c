/**
 * SurgeOS kernel.c
 * Kernel main file
 */

#include <kernel/kernel.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <stdio.h>
#include <string.h>

void kernel_main(void) {
  init_idt();
  term_init();

  printf("Hello!\n");

  while (1) {
    asm volatile("hlt");
  }
} 
