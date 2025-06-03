/**
 * SurgeOS libc stdlib/exit.c
 * `exit()` implementation
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void exit(int status) {
  // Flush all open streams
  fflush(NULL);

  // Close all open file descriptors
  for (int fd = 0; fd < sysconf(_SC_OPEN_MAX); fd++) {
    close(fd);
  }

  // Call any registered atexit handlers
  // TODO
  
  _exit(status);
}
