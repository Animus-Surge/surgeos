/**
 * SurgeOS libc stdio/putc.c
 * `putc()` implementation
 */

#include <stdio.h>

int putc(int c, FILE* stream) {
  return fputc(c, stream);
}

