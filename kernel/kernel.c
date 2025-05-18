/**
 * SurgeOS kernel.c
 * Kernel main file
 */

#include <kernel/kernel.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

void kernel_main(void) {
  init_idt();

  term_init();

  printf("SurgeOS Kernel\n");

  while (1) {
    asm volatile("hlt");
  }
} 
