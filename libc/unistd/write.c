/**
 * SurgeOS libc unistd/write.c
 * `write()` implementation
 */

#include <unistd.h>
#include "internal/syscall.h"

/**
 * Write data to a file descriptor.
 *
 * @param fd The file descriptor to write to.
 * @param buf The buffer containing the data to write.
 * @param count The number of bytes to write.
 * @return The number of bytes written, or -1 on error.
 */
ssize_t write(int fd, const void* buf, size_t count) {
  long res = syscall(SYS_WRITE, fd, (long)buf, count, 0, 0, 0);
  if (res < 0) {
    return -1; // Error occurred
  }
  return (ssize_t)res; // Return the number of bytes written
}

