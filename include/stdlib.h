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

__attribute__((__noreturn__)) void abort(void);

char* itoa(int, char*, int);

__EXTC_END

#endif // SURGEOS_STDLIB_H

