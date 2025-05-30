/**
 * SurgeOS kernel syscall.c
 * System call implementation
 */

#include <kernel/kernel.h>
#include <kernel/syscall.h>

#include <stdio.h>

int sys_write(int fd, const char* buf, size_t count) {
  if (fd == 1) { // stdout
    for (size_t i = 0; i < count; i++) {
      putchar(buf[i]);
    }
    return count;
  } else if (fd == 2) { // stderr
    for (size_t i = 0; i < count; i++) {
      putc(buf[i], stderr);
    }
    return count;
  }
  else {
    // Unsupported file descriptor
    return -1;
  }
}
