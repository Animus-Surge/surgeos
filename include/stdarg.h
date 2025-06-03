/**
 * SurgeOS libc stdarg.h
 * Variable argument handling
 */

#ifndef SURGEOS_STDARG_H
#define SURGEOS_STDARG_H

typedef char* va_list;

#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type)   __builtin_va_arg(ap, type)
#define va_end(ap)         __builtin_va_end(ap)
#define va_copy(dest, src) __builtin_va_copy(dest, src)

#endif // SURGEOS_STDARG_H
