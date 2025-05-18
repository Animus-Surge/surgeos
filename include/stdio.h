/**
 * SurgeOS include/stdio.h
 * stdio.h
 */

#ifndef SURGEOS_STDIO_H
#define SURGEOS_STDIO_H

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int puts(const char*);
int putchar(int);

#ifdef __cplusplus
}
#endif

#endif // SURGEOS_STDIO_H

