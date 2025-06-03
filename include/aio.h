/**
 * SurgeOS libc aio.h
 * Asynchronous I/O support
 */

#ifndef SURGEOS_AIO_H
#define SURGEOS_AIO_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <signal.h>

__EXTC

typedef struct {
  int aio_fildes;
  off_t aio_offset;
  volatile void* aio_buf;
  size_t aio_nbytes;
  int aio_reqprio;
  sigevent aio_sigevent;
  int aio_lio_opcode;
} aiocb;

#define AIO_CANCELLED 0x0
#define AIO_NOTCANCELLED 0x1
#define AIO_ALLDONE 0x2

#define LIO_WAIT 0x3
#define LIO_NOWAIT 0x4
#define LIO_READ 0x5
#define LIO_WRITE 0x6
#define LIO_NOP 0x7

int aio_cancel(int, aiocb*);
int aio_error(const aiocb*);
int aio_fsync(int, aiocb*);
int aio_read(aiocb*);
ssize_t aio_return(aiocb*);
int aio_suspend(const aiocb *const[], int, const timespec*);
int aio_write(aiocb*);
int lio_listio(int, aiocb* const[], int, sigevent*);

__EXTC_END

#endif
