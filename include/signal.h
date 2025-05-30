/**
 * SurgeOS libc signal.h
 * Signal handlers
 */

#ifndef SURGEOS_SIGNAL_H
#define SURGEOS_SIGNAL_H

_EXTC

#define SIGINT
#define SIGTERM
#define SIGABRT
#define SIGFPE
#define SIGSEGV
#define SIGILL

#define SIG_DFL(x)
#define SIG_IGN(x)
#define SIG_ERR(x)

#define SIG_ATOMIC_T_SIGNED
typedef char sig_atomic_t;

void signal(int, void*);

_EXTC_END

#endif /* SURGEOS_SIGNAL_H */


