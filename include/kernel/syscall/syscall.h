/**
 * SurgeOS kernel syscall/syscall.h
 * System calls header
 */

#ifndef SURGEOS_KERNEL_SYSCALL_SYSCALL_H
#define SURGEOS_KERNEL_SYSCALL_SYSCALL_H

enum syscall_number {
  SYS_WRITE = 0,
  SYS_EXIT = 1,
  SYS_READ = 2,
};

#ifdef __surgeos_kernel__

#include <stddef.h>

int sys_write(int, const char*, size_t);
void sys_exit(int);
void sys_read(int, char*, size_t);

#endif // __surgeos_kernel__

#endif // SURGEOS_KERNEL_SYSCALL_SYSCALL_H
