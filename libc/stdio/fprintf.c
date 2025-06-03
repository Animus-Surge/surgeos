/**
 * SurgeOS libc stdio/fprintf.c
 * `fprintf()` implementation
 */

#include <stdarg.h>
#include <stdio.h>

/**
 * Prints formatted output to specified file stream.
 * 
 * @param stream (FILE*) The file stream to output to
 * @param format (const char*) The format string
 * @return The number of characters outputted. -1 if errored (see errno).
 */
int fprintf(FILE* stream, const char* format, ...) {
  va_list params;
  va_start(params, format);
  int written = vfprintf(stream, format, params);
  va_end(params);
  return written;
}



