/**
 * SurgeOS libc stdio/putchar.c
 * `putchar()` implementation
 */

#include <stdio.h>

#if defined(__surgeos_libk__)
#include <kernel/tty.h>
#endif

int putchar(int ic) {
#if defined(__surgeos_libk__)
  char c = (char)ic;
  term_write(&c, 1);
#else
  putc(ic);
#endif
  return ic;
}

