/**
 * SurgeOS libc stdio/vfprintf.c
 * `vfprintf.c` implementation
 */

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// TODO: __surgeos_libk__ checking

/**
 * Format hexadecimal
 *
 * @param buf (char*) the buffer to use
 * @param stream (FILE*) the file stream to write to
 * @param value (uint32_t; long int) The value to format into
 * @param uppercase (bool) Whether or not to format as lowercase or uppercase hexadecimal (x, X)
 * @return The number of bytes written
 */
int fmt_hex(char* buf, FILE* stream, uint32_t value, bool uppercase) {
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
  fprint(stream, buf, written);

  return written;
}

int _handle_escapes(FILE* stream, char* buf) {
  if(*buf == '\\') {
    buf++;
    switch (*buf) {
      case 'n':
        fputc(stream, '\n');
        return 1;
      default:
        return 0;
    }
  }
}

int fmt_unsigned_int(FILE* stream, char* buf) {
  return 0;
}

int fmt_signed_int(FILE* stream, char* buf) {
  return 0;
}

/**
 * Prints formatted output to specified file stream
 *
 * @param stream (FILE*) The stream to output to
 * @param format (const char*) The input format
 * @param ap (va_list) The list of arguments
 * @return The number of bytes written. -1 if errored (see errno).
 */
int vfprintf(FILE* stream, const char* format, va_list ap) {
  int written = 0;
  char* p = format;

  while (*p != '\0') {
    size_t maxrem = INT_MAX - written;

    if (p[0] != '%' || p[1] == '%') {
      if (p[0] == '%') p++;
      if (p[0] == '\\') _handle_escapes(stream, p);

      size_t amount = 1;
      while(p[amount] && p[amount] != '%') amount++;

      if(maxrem < amount) {
        errno = EOVERFLOW;
        return -1;
      }
      if (!fprint(stream, p, amount)) return -1;

      p += amount;
      written += amount;
      continue;
    }

    const char* format_start = b++;

    if(*b == 'c') { // Character
      b++;
      char c = (char) va_arg(ap, int);
      if(!maxrem) {
        errno = EOVERFLOW;
        return -1;
      }
      if (!fprint(stream, &c, sizeof(c))) return -1;
      written++;
    } else if (*p == 's') { // String
      p++;
      const char* str = va_arg(ap, const char*);
      size_t len = strlen(str);
      if(maxrem < len) {
        errno = EOVERFLOW;
        return -1;
      }
      if(!fprint(stream, str, len)) return -1;
      written += len;
    }

    //TODO: decimal (i, d, u), hex (x, X), octal (o, O), floating point (f, F), 
    //storage pointer (n), pointers (p), hex floating point (a, A)
    
    else { // Everything else
      p = format_start;
      size_t len = strlen(p);
      if(maxrem < len) {
        errno = EOVERFLOW;
        return -1;
      }
      if (!fprint(stream, p, len)) return -1;
      written += len;
      p += len;
    } 
  }
  return written;
}

