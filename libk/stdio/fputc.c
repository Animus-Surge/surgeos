/**
 * SurgeOS libc stdio/fputc.c
 * `fputc()` implementation
 */

/**
 * Write a character to a stream. Sets `errno` if unsuccessful.
 * @param c (int/char) The character to write
 * @param stream (FILE*) the stream to write to
 * @return The character if successful, EOF (-1) otherwise
 */
int fputc(int c, FILE* stream) {
  return -1; // TODO: impl
}

