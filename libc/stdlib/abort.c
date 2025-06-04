/**
 * SurgeOS libc stdlib/abort.c
 * abort() implementation
 */

#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort() {
#ifdef __surgeos_libk__
  printf("kernel: panic: abort()\n");
  asm volatile("hlt");
#else
  // TODO
  printf("abort()");
#endif
  while (1) {}
  __builtin_unreachable();
}
