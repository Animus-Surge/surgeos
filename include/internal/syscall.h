/**
 * SurgeOS internal syscall interface
 */

#ifndef SURGEOS_INTERNAL_SYSCALL_H
#define SURGEOS_INTERNAL_SYSCALL_H

#include <sys/cdefs.h>
#include <sys/types.h>

#define SYS_WRITE 0
#define SYS_EXIT 1
#define SYS_READ 2

__EXTC

long syscall(int number, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

__EXTC_END

#endif // SURGEOS_INTERNAL_SYSCALL_H
