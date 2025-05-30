/**
 * SurgeOS libc errno.h
 * Errors header
 */

#ifndef SURGEOS_ERRNO_H
#define SURGEOS_ERRNO_H

#define EDOM
#define EILSEQ
#define ERANGE

extern int errno; // TODO: thread-safe

#endif /** SURGEOS_ERRNO_H */
