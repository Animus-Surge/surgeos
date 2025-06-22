/**
 * SurgeOS libk strcmp.c
 * `strcmp()` implementation
 */

#include <string.h>

int strcmp(const char* str1, const char* str2) {
  while (*str1 && *str2) {
    if (*str1 != *str2) {
      return (unsigned char)*str1 - (unsigned char)*str2;
    }
    str1++;
    str2++;
  }
  return 0;
}
