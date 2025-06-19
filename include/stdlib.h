/**
 * SurgeOS include/stdlib.h
 * stdlib.h
 */

#ifndef SURGEOS_STDLIB_H
#define SURGEOS_STDLIB_H

#include <sys/cdefs.h>
#include <stddef.h>

__EXTC

#define NULL ((void*)0)

__surgeos_noreturn void abort(void);
__surgeos_noreturn void panic(const char* msg);
__surgeos_noreturn void panicf(const char* fmt, ...);


char* itoa(int, char*, int);

__EXTC_END

#endif // SURGEOS_STDLIB_H

