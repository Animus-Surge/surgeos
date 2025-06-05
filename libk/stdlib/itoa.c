/**
 * SurgeOS stdlib/itoa.c
 * `itoa()` implementation.
 */

#include <stdlib.h>

char* itoa(int value, char* buffer, int base) {
  if (base < 2 || base > 36) {
    *buffer = '\0'; // Invalid base
    return buffer;
  }

  char* ptr = buffer;
  int is_negative = 0;

  if (value < 0 && base == 10) {
    is_negative = 1;
    value = -value;
  }

  do {
    int digit = value % base;
    *ptr++ = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
    value /= base;
  } while (value != 0);

  if (is_negative) {
    *ptr++ = '-';
  }

  *ptr = '\0';

  // Reverse the string
  char* start = buffer;
  char* end = ptr - 1;
  while (start < end) {
    char temp = *start;
    *start++ = *end;
    *end-- = temp;
  }

  return buffer;
}
