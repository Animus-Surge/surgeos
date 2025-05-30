#ifndef SURGEOS_SYS_MMAN_H
#define SURGEOS_SYS_MMAN_H

#include <sys/cdefs.h>
#include <sys/types.h>

__EXTC

//Protection options
#define PROT_NONE 0x0
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4

//Mapping flags
#define MAP_SHARED 0x01
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define MAP_FIXED 0x10

//msync flags
#define MS_ASYNC 0x01
#define MS_SYNC 0x02
#define MS_INVALIDATE 0x04

//mlockall flags
#define MCL_CURRENT 0x01
#define MCL_FUTURE 0x02

int mlock(const void*, size_t);
int mlockall(int);
void* mmap(void*, size_t, int, int, int, off_t);
int mprotect(void*, size_t, int);
int msync(void*, size_t, int);
int munlock(const void*, size_t);
int munlockall(void);
int munmap(void*, size_t);

int shm_open(const char*, int, mode_t);
int shm_unlink(const char*);

__EXTC_END

#endif // SURGEOS_SYS_MMAN_H
