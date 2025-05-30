/**
 * SurgeOS unistd.h
 * Standard symbolic constants and types
 */

#ifndef SURGEOS_UNISTD_H
#define SURGEOS_UNISTD_H

#include <sys/cdefs.h>

// TODO: POSIX and compliance macros

#define NULL ((void*)0)

// access() constants
#define R_OK 0x04
#define W_OK 0x02
#define X_OK 0x01
#define F_OK 0x00

// File descriptor constants
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

// lseek(), fcntl() constants
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

__EXTC

// Types
typedef unsigned long size_t;
typedef long ssize_t;
typedef long off_t;
typedef int pid_t;
typedef unsigned long uid_t;
typedef unsigned long gid_t;
typedef unsigned int useconds_t;
typedef int* intptr_t;

// Functions

void _exit(int);

ssize_t read(int, void*, size_t);
ssize_t write(int, const void*, size_t);

__EXTC_END

#endif /* SURGEOS_UNISTD_H */
