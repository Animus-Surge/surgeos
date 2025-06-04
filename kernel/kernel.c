/**
 * SurgeOS kernel.c
 * Kernel main file
 */

#include <kernel/kernel.h>
#include <kernel/tty.h>
#include <stdio.h>
#include <string.h>

void print_banner(void) {
  for (size_t i = 0, j = 0; j < 32; j++) {
    if (j % 2 == 1) {
      if (i % 8 == 0) {
        term_putchar('\n');
      }
      i++;
    }
    term_set_color(i << 4);
    term_putchar(' ');
  }

  term_putchar('\n');
  term_set_color(0x0F); // Reset color to white
  term_writestr("SurgeOS Kernel v0.1\n");
}

void kernel_main(void) {
  init_idt();

  term_init();

  print_banner();

  printf("surgeos> ");

  while (1) {
    asm volatile("hlt");
  }
} 
