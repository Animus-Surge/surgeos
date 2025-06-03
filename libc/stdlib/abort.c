/**
 * SurgeOS libc stdlib/abort.c
 * abort() implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

noreturn void abort() {
#ifdef __surgeos_libk__
  printf("kernel: panic: abort()\n");
  asm volatile("hlt");
#else
  printf("abort()\n");
  _exit(EXIT_FAILURE);
#endif
  while (1) {}
  __builtin_unreachable();
}
