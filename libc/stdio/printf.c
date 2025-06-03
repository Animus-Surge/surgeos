/**
 * SurgeOS libc stdio/printf.c
 * `printf()` implementation
 */

#include <stdarg.h>
#include <stdio.h>

/**
 * Prints formatted output to stdout
 *
 * @param format (const char*) The format string
 * @returns Number of bytes written. -1 if errored (see errno);
 */
int printf(const char* format, ...) {
  va_list params;
  va_start(params, format);
  int written = vfprintf(stdout, format, params);
  va_end(params);
  return written;
}

