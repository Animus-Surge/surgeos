/**
 * SurgeOS libc stdio/printf.c
 * `printf()` implementation
 */

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <kernel/tty.h>

int print(const char* str, size_t len) {
  if (len == 0) return 0; // Nothing to print

  // Write to the terminal
  for (size_t i = 0; i < len; i++) {
    term_putchar(str[i]);
  }

  return len; // Return the number of characters printed
}

int putc(int c) {
  term_putchar(c);
  return c; // Return the character written
}

/**
 * Format hexadecimal
 *
 * @param buf (char*) the buffer to use
 * @param stream (FILE*) the file stream to write to
 * @param value (uint32_t; long int) The value to format into
 * @param uppercase (bool) Whether or not to format as lowercase or uppercase hexadecimal (x, X)
 * @return The number of bytes written
 */
int fmt_hex(char* buf, uint32_t value, bool uppercase) {
  static const char hex_lower[] = "0123456789abcdef";
  static const char hex_upper[] = "0123456789ABCDEF";

  char temp[8];
  int i = 0;

  if(uppercase) {
    do {
      temp[i++] = hex_upper[value & 0xF];
      value >>= 4;
    } while (value);
  } else {
    do {
      temp[i++] = hex_lower[value & 0xF];
      value >>= 4;
    } while (value);
  }

  int written = 0;
  while(i--) {
    *buf++ = temp[i];
    written++;
  }
  print(buf, written);
  return written;
}

int _handle_escapes(char* buf) {
  if(*buf == '\\') {
    buf++;
    switch (*buf) {
      case 'n':
        putc('\n');
        return 1;
      default:
        return 0;
    }
  }
}

/**
 * Prints formatted output to specified file stream
 *
 * @param stream (FILE*) The stream to output to
 * @param format (const char*) The input format
 * @param ap (va_list) The list of arguments
 * @return The number of bytes written. -1 if errored (see errno).
 */
int printf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);

  int written = 0;
  char* p = format;

  while (*p != '\0') {
    size_t maxrem = INT_MAX - written;

    if (p[0] != '%' || p[1] == '%') {
      if (p[0] == '%') p++;
      if (p[0] == '\\') _handle_escapes(p);

      size_t amount = 1;
      while(p[amount] && p[amount] != '%') amount++;

      if(maxrem < amount) {
        return -1;
      }
      if (!print(p, amount)) return -1;

      p += amount;
      written += amount;
      continue;
    }

    const char* format_start = p++;

    if(*p == 'c') { // Character
      p++;
      char c = (char) va_arg(ap, int);
      if(!maxrem) {
        return -1;
      }
      if (!print(&c, sizeof(c))) return -1;
      written++;
    } else if (*p == 's') { // String
      p++;
      const char* str = va_arg(ap, const char*);
      size_t len = strlen(str);
      if(maxrem < len) {
        return -1;
      }
      if(!print(str, len)) return -1;
      written += len;
    } else if (*p == 'd' || *p == 'i') { // Decimal integer
      p++;
      int value = va_arg(ap, int);
      char buf[12]; // Enough for 32-bit signed int
      itoa(value, buf, 10);
      size_t len = strlen(buf);
      if(maxrem < len) {
        return -1;
      }
      if (!print(buf, len)) return -1;
      written += len;
    } else if (*p == 'u') { // Unsigned integer
      p++;
      unsigned int value = va_arg(ap, unsigned int);
      char buf[12]; // Enough for 32-bit unsigned int
      itoa(value, buf, 10);
      size_t len = strlen(buf);
      if(maxrem < len) {
        return -1;
      }
      if (!print(buf, len)) return -1;
      written += len;
    } else if (*p == 'x' || *p == 'X') { // Hexadecimal
      bool uppercase = (*p == 'X');
      p++;
      unsigned int value = va_arg(ap, unsigned int);
      char buf[9]; // Enough for 32-bit hex
      fmt_hex(buf, value, uppercase);
      size_t len = strlen(buf);
      if(maxrem < len) {
        return -1;
      }
      if (!print(buf, len)) return -1;
      written += len;
    } else if (*p == 'l') { // Long integer (not fully implemented)
      p++;
    } else if (*p == 'f') { // Floating point (not implemented)
      p++;
    } else if (*p == 'n') { // Storage pointer (not implemented)
      p++;
    } else if (*p == 'p') { // Pointer (not implemented)
      p++;
    }

    //TODO: decimal (i, d, u), hex (x, X), octal (o, O), floating point (f, F), 
    //storage pointer (n), pointers (p), hex floating point (a, A)
    
    else { // Everything else
      p = format_start;
      size_t len = strlen(p);
      if(maxrem < len) {
        return -1;
      }
      if (!print(p, len)) return -1;
      written += len;
      p += len;
    } 
  }

  va_end(ap);
  return written;
}
