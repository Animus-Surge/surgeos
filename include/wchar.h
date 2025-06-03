/**
 * SurgeOS libc wchar.h
 * Wide character support
 */

#ifndef SURGEOS_WCHAR_H
#define SURGEOS_WCHAR_H

#include <sys/cdefs.h>

#include <stddef.h>
#include <stdio.h>

__EXTC

typedef unsigned long wchar_t;
typedef unsigned long wint_t;
typedef unsigned long wctype_t;
typedef struct {
    int __count;
    wchar_t __value;
} mbstate_t;

#define WEOF ((wint_t)-1)
#define WCHAR_MIN 0
#define WCHAR_MAX 0xFFFFFFFFUL
#define NULL ((wchar_t *)0)

wint_t btowc(int);

__EXTC_END

#endif // SURGEOS_WCHAR_H

