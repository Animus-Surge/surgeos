/**
 * SurgeOS libk strncat.c
 * `strncat()` implementation
 */

#include <string.h>

char* strncat(char* dest, const char* src, size_t n) {
  if (dest == NULL || src == NULL) {
    return NULL; // Handle null pointers gracefully
  }

  char* original_dest = dest;

  // Move to the end of the destination string
  while (*dest != '\0') {
    dest++;
  }

  // Append up to n characters from src
  while (n-- && *src != '\0') {
    *dest++ = *src++;
  }

  // Null-terminate the destination string
  *dest = '\0';

  return original_dest; // Return the original destination pointer
}
