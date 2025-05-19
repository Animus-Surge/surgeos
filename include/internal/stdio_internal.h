/**
 * SurgeOS libc private stdio_internal.h
 * Internal structs for stdio.h
 */

#ifndef SURGEOS_STDIO_INTERNAL_H
#define SURGEOS_STDIO_INTERNAL_H

struct _File {
  int fd;
  int flags;
  unsigned char* buf;
  size_t buf_size;
  size_t pos;
  size_t len;
  int error;
  int eof;
  int ungetc_buf;
  int has_ungetc;
};

#endif /** SURGEOS_STDIO_INTERNAL_H */
