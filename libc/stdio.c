/**
 * SurgeOS libc stdio.c
 * Standard I/O definitions
 */

#include <stdio.h>

#if defined(__surgeos_libk__)
#include <kernel/tty.h>
#endif

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>

static bool print(const char* data, size_t length) {
  const unsigned char* bytes = (const unsigned char*) data;
  for (size_t i = 0; i < length; i++)
    if (putchar(bytes[i]) == EOF)
      return false;
  return true;
}

int puts(const char* str) {
  return printf("%s\n", str);
}

int putchar(int ic) {
#if defined(__surgeos_libk__)
  char c = (char)ic;
  term_write(&c, 1);
#else
  //TODO: syscall/stdio implementation
#endif
  return ic;
}

static bool print_int(int i) {
  char buf[12]; // Enough for 32-bit int
  int len = 0;
  if (i < 0) {
    buf[len++] = '-';
    i = -i;
  }
  if (i == 0) {
    buf[len++] = '0';
  } else {
    while (i > 0) {
      buf[len++] = '0' + (i % 10);
      i /= 10;
    }
  }
  // Reverse the string
  for (int j = 0; j < len / 2; j++) {
    char temp = buf[j];
    buf[j] = buf[len - j - 1];
    buf[len - j - 1] = temp;
  }
  buf[len] = '\0';
  return print(buf, len);
}

int fmt_x(char *buf, uint32_t value) {
  static const char hex[] = "0123456789abcdef";
  char temp[8];  // Enough for 32-bit hex
  int i = 0;

  // Convert to hex backwards
  do {
    temp[i++] = hex[value & 0xF];
    value >>= 4;
  } while (value);

  // Write to output buffer in correct order
  int written = 0;
  while (i--) {
    *buf++ = temp[i];
    written++;
  }
  print(buf, written);

  return written;
}

int handle_escape_sequence(char *buf) {
  if (*buf == '\\') {
    buf++;
    switch (*buf) {
      case 'n':
        putchar('\n');
        return 1;
      case 't':
        putchar('\t');
        return 1;
      case 'r':
        putchar('\r');
        return 1;
      default:
        return 0; // Unknown escape sequence, ignore
    }
  }
}

int printf(const char* restrict format, ...) {
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while (*format != '\0') {
    size_t maxrem = INT_MAX - written;

    if (format[0] != '%' || format[1] == '%') {
      if (format[0] == '%')
        format++;
      if (format[0] == '\\') {
        written += handle_escape_sequence((char*)format);
      }
      size_t amount = 1;
      while (format[amount] && format[amount] != '%')
        amount++;
      if (maxrem < amount) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, amount))
        return -1;
      format += amount;
      written += amount;
      continue;
    }

    const char* format_begun_at = format++;

    if (*format == 'c') {
      format++;
      char c = (char) va_arg(parameters, int /* char promotes to int */);
      if (!maxrem) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(&c, sizeof(c)))
        return -1;
      written++;
    } else if (*format == 's') {
      format++;
      const char* str = va_arg(parameters, const char*);
      size_t len = strlen(str);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(str, len))
        return -1;
      written += len;
    } else if (*format == 'x') {
      format++;
      uint32_t value = va_arg(parameters, uint32_t);
      written += fmt_x((char*)format, value);
    } else {
      format = format_begun_at;
      size_t len = strlen(format);
      if (maxrem < len) {
        // TODO: Set errno to EOVERFLOW.
        return -1;
      }
      if (!print(format, len))
        return -1;
      written += len;
      format += len;
    }
  }

  va_end(parameters);
  return written;
}
