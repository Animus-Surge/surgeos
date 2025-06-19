/**
 * SurgeOS libk panic.c
 * Kernel panic functions
 */

#include <kernel/vga.h>
#include <kernel/driver/serial.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void panicf(const char* fmt, ...) {
/*
  va_list args;
  va_start(args, fmt);

  char buf[256];
  vsprintf(buf, fmt, args);

  va_end(args);

  init_fallback_vga();
  fallback_vga_print(buf, strlen(buf));

  while (1) {
    asm volatile("hlt"); // Halt the system
  }
*/
}

void panic(const char* msg) {
  init_fallback_vga();
  serial_printf("Kernel panic: %s\n", msg);
  vga_draws(msg, 0, 0, (uint32_t)vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
  
  // Halt the system
  while (1) {
    asm volatile("hlt");
  }
}
