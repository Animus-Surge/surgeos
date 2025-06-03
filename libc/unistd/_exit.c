/**
 * SurgeOS libc unistd/_exit.c
 * `_exit()` implementation
 */

#include <unistd.h>

#include "internal/syscall.h"

/**
 * Terminate the process immediately without cleanup.
 *
 * This function is used to exit the process without invoking any
 * cleanup handlers or flushing stdio buffers.
 *
 * @param status The exit status of the process.
 */
void _exit(int status) {
  syscall(SYS_EXIT, status, 0, 0, 0, 0, 0);
  
  while (1) {}
}

