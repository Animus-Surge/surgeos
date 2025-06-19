/**
 * SurgeOS libk vsnprintf.c
 * vsnprintf() implementation
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include <_formatting.h>

/**
 * @brief Format a string with variable arguments
 *
 * @param buf (char*) The buffer to write the formatted string to
 * @param size (size_t) The size of the buffer
 * @param format (const char*) The format string
 * @param ap (va_list) The variable argument list
 * @return The number of characters written, or a negative value on error
 */
int vsnprintf(char* buf, size_t size, const char* format, va_list ap) {
  if(size == 0 || buf == NULL || format == NULL) {
    return -1; // Invalid parameters
  }

  size_t written = 0;
  const char* p = format;

  while (*p != '\0') {
    size_t maxrem = size - written;

    if (p[0] != '%' || p[1] == '%') {
      if (p[0] == '%') p++;
      if (p[0] == '\\') {
        // Handle escape sequences
        if (*p == 'n') {
          if (maxrem < 1) return -1;
          buf[written++] = '\n';
          p++;
          continue;
        }
        if (*p == 't') {
          if (maxrem < 1) return -1;
          buf[written++] = '\t';
          p++;
          continue;
        }
        if (*p == 'r') {
          if (maxrem < 1) return -1;
          buf[written++] = '\r';
          p++;
          continue;
        }
        if (*p == 'b') {
          if (maxrem < 1) return -1;
          buf[written++] = '\b';
          p++;
          continue;
        }

        //Literals
        if (*p == '\\') {
          if (maxrem < 1) return -1;
          buf[written++] = '\\';
          p++;
          continue;
        }
        if (*p == '\'') {
          if (maxrem < 1) return -1;
          buf[written++] = '\'';
          p++;
          continue;
        }
        if (*p == '\"') {
          if (maxrem < 1) return -1;
          buf[written++] = '\"';
          p++;
          continue;
        }
        if (*p == '0') {
          if (maxrem < 1) return -1;
          buf[written++] = '\0'; // Null character
          p++;
          continue;
        }
        if (*p == '%') {
          if (maxrem < 1) return -1;
          buf[written++] = '%'; // Literal percent sign
          p++;
          continue;
        }

      }

      size_t amount = 1;
      while (p[amount] && p[amount] != '%') amount++;

      if (maxrem < amount) return -1;
      memcpy(buf + written, p, amount);
      written += amount;
      p += amount;
      continue;
    }

    const char* format_start = p++;
    
    // Handle format specifiers
    if (*p == 'c') { // Character
      p++;
      char c = (char) va_arg(ap, int);
      if (maxrem < 1) return -1;
      buf[written++] = c;
    } else if (*p == 's') { // String
      p++;
      const char* str = va_arg(ap, const char*);
      size_t len = strlen(str);
      if (maxrem < len) return -1;
      memcpy(buf + written, str, len);
      written += len;
    } else if (*p == 'd' || *p == 'i') { // Decimal integer
      p++;
      int value = va_arg(ap, int);
      char temp[12]; // Enough for 32-bit signed int
      int len = fmt_int(temp, value);
      if (maxrem < len) return -1;
      memcpy(buf + written, temp, len);
      written += len;
    } else if (*p == 'u') { // Unsigned integer
      p++;
      unsigned int value = va_arg(ap, unsigned int);
      char temp[12]; // Enough for 32-bit unsigned int
      int len = fmt_uint(temp, value);
      if (maxrem < len) return -1;
      memcpy(buf + written, temp, len);
      written += len;
    } else if (*p == 'x' || *p == 'X') { // Hexadecimal
      bool uppercase = (*p == 'X');
      p++;
      unsigned int value = va_arg(ap, unsigned int);
      char temp[9]; // Enough for 32-bit hex
      int len = fmt_hex(temp, value, uppercase);
      if (maxrem < len) return -1;
      memcpy(buf + written, temp, len);
      written += len;
    } else if (*p == 'l') { // Long integer (not fully implemented)
      p++;
    } else if (*p == 'f') { // Floating point (not implemented)
      p++;
    } else if (*p == 'n') { // Storage pointer (not implemented)
      p++;
    } else if (*p == 'p') { // Pointer (not implemented)
      p++;
    } else {
      // Handle other format specifiers...
    }
  }

  buf[written] = '\0'; // Null-terminate the string
  return (int)written; // Return the number of characters written
}
