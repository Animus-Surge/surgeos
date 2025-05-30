/**
 * SurgeOS sys/wait.h
 * Wait macros and types
 */

#ifndef SURGEOS_SYS_WAIT_H
#define SURGEOS_SYS_WAIT_H

#include <sys/cdefs.h>
#include <sys/types.h>

__EXTC

#define WNOHANG 0x01
#define WUNTRACED 0x02

#define WEXITED 0x00
#define WSTOPPED 0x01
#define WCONTINUED 0x02
#define WNOHANG 0x04
#define WNOWAIT 0x08

#define WEXITSTATUS(status) (((status) & 0xFF00) >> 8)
#define WIFCONTINUED(status) (((status) & 0xFF) == 0x7F)
#define WIFEXITED(status) (((status) & 0xFF) == 0)
#define WIFSIGNALED(status) (((status) & 0xFF) != 0 && !WIFEXITED(status))
#define WIFSTOPPED(status) (((status) & 0xFF) == 0x7F)
#define WSTOPSIG(status) ((status) & 0x7F)
#define WTERMSIG(status) ((status) & 0x7F)

typedef enum {
    P_ALL,
    P_PID,
    P_PGID
} idtype_t;

pid_t wait(int*);
pid_t wait3(int*, int, struct rusage*);
int waitid(idtype_t, id_t, siginfo_t, int);
pid_t waitpid(pid_t, int*, int);

__EXTC_END

#endif /* SURGEOS_SYS_WAIT_H */
