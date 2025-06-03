/**
 * SurgeOS libc unistd/read.c
 * `read()` implementation
 */

#include <unistd.h>
#include "internal/syscall.h"

/**
 * Read data from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @param buf The buffer to store the read data.
 * @param count The number of bytes to read.
 * @return The number of bytes read, or -1 on error.
 */
ssize_t read(int fd, void* buf, size_t count) {
  long res = syscall(SYS_READ, fd, (long)buf, count, 0, 0, 0);
  if (res < 0) {
    return -1; // Error occurred
  }
  return (ssize_t)res; // Return the number of bytes read
}

