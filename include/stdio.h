/**
 * SurgeOS include/stdio.h
 * Standard Input/Output header
 */

#ifndef SURGEOS_STDIO_H
#define SURGEOS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#ifndef NULL
# define NULL ((void*)0)
#endif

// Formatted I/O
int printf(const char* __restrict format, ...);
int sprintf(char* __restrict str, const char* __restrict format, ...);
int snprintf(char* __restrict str, size_t size, const char* __restrict format, ...);
int vprintf(const char* __restrict format, va_list ap);
int vsnprintf(char* __restrict str, size_t size, const char* __restrict format, va_list ap);

#endif // SURGEOS_STDIO_H

