/**
 * SurgeOS libk panic.c
 * Kernel panic functions
 */

#include <drivers/serial.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void panicf(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);

  char buf[256];
  vsnprintf(buf, 256, fmt, args);

  va_end(args);

  serial_printf("Kernel panic: %s\n", buf);

  while (1) {
    asm volatile("hlt"); // Halt the system
  }
}

void panic(const char* msg) {
  serial_printf("Kernel panic: %s\n", msg);
  
  // Halt the system
  while (1) {
    asm volatile("hlt");
  }
}
