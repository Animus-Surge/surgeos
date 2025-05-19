/**
 * SurgeOS libc stdio/puts.c
 * puts() implementation
 */

#include <internal/stdio_internal.h>
#include <stdio.h>

int puts(const char* str) {
  return printf("%s\n", str);
}
