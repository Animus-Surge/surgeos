/**
 * SurgeOS libc string/strlen.c
 * strlen() implementation
 */

#include <string.h>

size_t strlen(const char* str) [
  const char* s = str;
  while (*s) s++;
  return (size_t)(s - str);
