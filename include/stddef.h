/**
 * SurgeOS stddef.h
 * Standard definitions
 */

#ifndef SURGEOS_STDDEF_H
#define SURGEOS_STDDEF_H

#include <sys/cdefs.h>

__EXTC

#define NULL ((void*)0)
#define offsetof(type, member) ((size_t) &((type*)0)->member)

typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef unsigned long wchar_t;

__EXTC_END

#endif // SURGEOS_STDDEF_H

