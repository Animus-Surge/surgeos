/**
 * SurgeOS include/stdio.h
 * Standard Input/Output header
 */

#ifndef SURGEOS_STDIO_H
#define SURGEOS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#define NULL ((void*)0)

// Formatted I/O
int printf(const char* __restrict format, ...);

#endif // SURGEOS_STDIO_H

