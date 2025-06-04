/**
 * SurgeOS stdio.c
 * Standard Input/Output implementation
 */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "internal/stdio_internal.h"

static FILE __file_objects[3];

FILE* stdin = &__file_objects[0];
FILE* stdout = &__file_objects[1];
FILE* stderr = &__file_objects[2];

static char stdin_buf[BUFSIZ];
static char stdout_buf[BUFSIZ];
static char stderr_buf[BUFSIZ];

static FILE* streams[FOPEN_MAX];

/**
 * Initializes stdio streams
 */
void __init_stdio_streams() {
  // File descriptors
  stdin->fd = STDIN_FILENO;
  stdout->fd = STDOUT_FILENO;
  stderr->fd = STDERR_FILENO;

  // Buffers
  stdin->buf = stdin_buf;
  stdout->buf = stdout_buf;
  stderr->buf = stderr_buf;

  stdin->active = true;
  stdout->active = true;
  stderr->active = true;

  // Position and sizes
  stdin->buf_size = BUFSIZ;
  stdout->buf_size = BUFSIZ;
  stderr->buf_size = BUFSIZ;
  stdin->pos = 0;
  stdout->pos = 0;
  stderr->pos = 0;

  // Flags
  stdin->flags = FILE_READ;
  stdout->flags = FILE_WRITE;
  stderr->flags = FILE_WRITE;

  // Modes
  stdin->mode = _IOLBF;
  stdout->mode = _IOLBF;
  stderr->mode = _IONBF; // Immediate errors, no buffering
}

// TODO:descriptive error return codes

/**
 * Flush specified stream; write all bytes in its buffer
 * @param stream (FILE*) the stream to flush
 * @returns 0 if successful, -1 otherwise
 */
int __flush_stream(FILE* stream) {
  if(!stream || !(stream->flags & FILE_WRITE) || !(stream->flags & FILE_DIRTY)) {
    return 0;
  }

  if (stream->count > 0) {
    ssize_t written = write(stream->fd, stream->buf, stream->count);
    if(written < 0) {
      stream->flags |= FILE_ERR;
      return EOF;
    }

    stream->pos = 0;
    stream->count = 0;
    stream->flags = ~FILE_DIRTY;
  }
  return 0;
}

int fprint(FILE* stream, const char* buf, size_t len) {
  for(size_t i = 0; i < len; i++) {
    if (putc(buf[i], stream) == EOF) {
      return EOF;
    }
  }
  return len;
}

