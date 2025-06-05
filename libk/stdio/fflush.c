/**
 * SurgeOS libc stdio/fflush.c
 * `fflush()` implementation
 */

#include <stdio.h>
#include "internal/stdio_internal.h"

int fflush(FILE* stream) {
  if(stream == NULL) return 0; // TODO: flush all
  return __flush_stream(stream);
}

