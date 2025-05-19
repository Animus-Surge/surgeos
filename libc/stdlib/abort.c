/**
 * SurgeOS libc stdlib/abort.c
 * abort() implementation
 */

#include <stdio.h>
#include <stdlib.h>

noreturn void abort() {
#ifdef __surgeos_libk__
  printf("kernel: panic: abort()\n");
  asm volatile("hlt");
#else
  printf("abort()\n");
#endif
  while (1) {}
  __builtin_unreachable();
}
