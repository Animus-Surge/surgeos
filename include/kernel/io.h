/**
 * SurgeOS kernel io.h
 * Kernel IO functions
 */

#ifndef SURGEOS_KERNEL_IO_H
#define SURGEOS_KERNEL_IO_H

#include <stdarg.h>

# if defined(__surgeos_libk__)

int printk(const char*, ...);

# endif // defined __surgeos_libk__

#endif // SURGEOS_KERNEL_IO_H
