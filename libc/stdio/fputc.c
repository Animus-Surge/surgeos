/**
 * SurgeOS libc stdio/fputc.c
 * `fputc()` implementation
 */

#include <errno.h>
#include <stdio.h>
#include "internal/stdio_internal.h"

/**
 * Write a character to a stream. Sets `errno` if unsuccessful.
 * @param c (int/char) The character to write
 * @param stream (FILE*) the stream to write to
 * @return The character if successful, EOF (-1) otherwise
 */
int fputc(int c, FILE* stream) {
  if(!stream || !(stream->flags & FILE_WRITE)) {
    errno = EBADF;
    return EOF;
  }

  //Handle unbuffered mode
  if (stream->mode == _IONBF) {
    char ch = (char)c;
    ssize_t written = write(stream->fd, &ch, 1);
    if(written != 1) {
      stream->flags |= FILE_ERR;
      return EOF;
    }
    stream->pos++;
    return (unsigned char)c;
  }

  //Handle buffered mode
  if(stream->pos >= (stream->buf + stream->buf_size)) {
    if(__flush_stream(stream) == EOF) {
      return EOF;
    }
  }

  *stream->pos++ = (char)c;
  stream->count++;
  stream->flags |= FILE_DIRTY;

  if(stream->mode == _IOLBF && c == '\n') {
    if(__flush_stream(stream) == EOF) {
      return EOF;
    }
  }

  stream->pos++;
  return (unsigned char)c;
}

