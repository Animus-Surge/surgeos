/**
 * SurgeOS libk formatting.c
 * Formatting utilities implementation; used for printf-like functions
 */

#include <_formatting.h>

int fmt_hex(char* buf, uint32_t value, bool uppercase) {
  static const char hex_lower[] = "0123456789abcdef";
  static const char hex_upper[] = "0123456789ABCDEF";

  char temp[8];
  int i = 0;

  if (uppercase) {
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

  // Reverse the string
  for (int j = 0; j < i; j++) {
    buf[j] = temp[i - j - 1];
  }
  buf[i] = '\0'; // Null-terminate the string

  return i; // Return the number of characters written
}

int fmt_int(char* buf, int value) {
  int written = 0;
  if (value < 0) {
    buf[written++] = '-';
    value = -value;
  }
  written += fmt_uint(buf + written, (unsigned int)value);
  return written;
}

int fmt_uint(char* buf, unsigned int value) {
  int written = 0;
  if (value == 0) {
    buf[written++] = '0';
  } else {
    char temp[10]; // Enough for 32-bit unsigned int
    int i = 0;
    while (value > 0) {
      temp[i++] = '0' + (value % 10);
      value /= 10;
    }
    // Reverse the string
    for (int j = 0; j < i; j++) {
      buf[written++] = temp[i - j - 1];
    }
  }
  buf[written] = '\0'; // Null-terminate the string
  return written;
}

int fmt_string(char* buf, const char* str) {
  int written = 0;
  while (*str) {
    buf[written++] = *str++;
  }
  buf[written] = '\0'; // Null-terminate the string
  return written;
}

int fmt_char(char* buf, char c) {
  buf[0] = c;
  buf[1] = '\0'; // Null-terminate the string
  return 1; // Return the number of characters written
}
