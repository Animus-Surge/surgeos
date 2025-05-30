/**
 * SurgeOS include/string.h
 * string.h
 */

#ifndef SURGEOS_STRING_H
#define SURGEOS_STRING_H

#include <sys/cdefs.h>
#include <stddef.h>

__EXTC

# ifndef SIZE_T_DEFINED
#  define SIZE_T_DEFINED
typedef unsigned long size_t;
# endif

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);

size_t strlen(const char*);
char* strcat(char*, const char*);
char* strcpy(char*, const char*);
char* strchr(const char*, int);

__EXTC_END

#endif // SURGEOS_STRING_H

