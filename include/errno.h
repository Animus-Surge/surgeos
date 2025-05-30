/**
 * SurgeOS libc errno.h
 * Errors header
 */

#ifndef SURGEOS_ERRNO_H
#define SURGEOS_ERRNO_H

#define EDOM          1
#define EILSEQ        2
#define ERANGE        3
#define EOVERFLOW     4
#define EBADF         5

extern int errno; // TODO: thread-safe

#endif /** SURGEOS_ERRNO_H */
