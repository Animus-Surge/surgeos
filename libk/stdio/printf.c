/**
 * SurgeOS libc stdio/printf.c
 * `printf()` implementation
 */

#include <drivers/tty.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

/**
 * @brief Print formatted output to the standard output
 *
 * This function formats the given string using the provided format and variable arguments,
 * and writes the result to the standard output (TTY).
 *
 * @param format The format string
 * @param ... The variable arguments to format
 * @return The number of characters written, or -1 on error
 */
int printf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[1024]; // Temporary buffer for formatted output
  int result = vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  if (result < 0) {
    return -1; // Error in formatting
  }

  tty_write(buffer, result);
  return result;
}
