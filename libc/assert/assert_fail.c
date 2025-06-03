/**
 * SurgeOS libc assert/assert_fail.c
 * `__assert_fail()` implementation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void __assert_fail(const char *assertion, const char *file, unsigned int line,
                   const char *function) {
  return; // TODO: impl
}
