/**
 * SurgeOS libc private stdio_internal.h
 * Internal structs for stdio.h
 */

#ifndef SURGEOS_STDIO_INTERNAL_H
#define SURGEOS_STDIO_INTERNAL_H

#include <stdbool.h>
#include <stddef.h>

struct _File {
  int fd;
  int flags;
  int mode;
  long pos;
  bool active;
  unsigned char* buf;
  size_t buf_size;
  unsigned char* pos;
  size_t count;
};

void __init_stdio_streams(void);
void __flush_stream(FILE*);

#endif /** SURGEOS_STDIO_INTERNAL_H */
