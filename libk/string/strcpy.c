/**
 * SurgeOS libk strcpy.c
 * `strcpy()` implementation
 */

#include <string.h>

char* strcpy(char* dest, const char* src) {
  if (dest == NULL || src == NULL) {
    return NULL; // Handle null pointers gracefully
  }

  while (*src != '\0') {
    *dest++ = *src++;
  }
  *dest = '\0'; // Null-terminate the destination stringa
  return dest - (src - dest); // Return the original destination pointer
}
