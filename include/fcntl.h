/**
 * SurgeOS fcntl.h
 * File control
 */

#ifndef SURGEOS_FCNTL_H
# define SURGEOS_FCNTL_H

# ifndef FCNTL_CMD_OPTS_DEFINED
#  define FCNTL_CMD_OPTS_DEFINED
#  define F_DUPFD 0x01
#  define F_GETFD 0x02
#  define F_SETFD 0x03
#  define F_GETFL 0x04
#  define F_SETFL 0x05
#  define F_GETLK 0x06
#  define F_SETLK 0x07
#  define F_SETLKW 0x08
# endif // FCNTL_CMD_OPTS_DEFINED

# ifndef FD_CLOEXEC
#  define FD_CLOEXEC 0x01
# endif // FD_CLOEXEC

# ifndef FCNTL_LTYPE_VALS_DEFINED
#  define FCNTL_LTYPE_VALS_DEFINED
#  define F_RDLCK 0x01
#  define F_WRLCK 0x02
#  define F_UNLCK 0x03
# endif // FCNTL_LTYPE_VALS_DEFINED

# ifndef OPEN_OFLAGS_DEFINED
#  define OPEN_OFLAGS_DEFINED
#  define O_CREAT 0x01
#  define O_EXCL 0x02
#  define O_NOCTTY 0x04
#  define O_TRUNC 0x08
# endif

# ifndef FSTAT_FLAGS_DEFINED
#  define FSTAT_FLAGS_DEFINED
#  define O_APPEND 0x10
#  define O_NONBLOCK 0x20
#  define O_DSYNC 0x40
#  define O_SYNC 0x80
#  define O_RSYNC 0x100
# endif // FSTAT_FLAGS_DEFINED

# ifndef O_ACCMODE
# define O_ACCMODE 0x03
# endif // O_ACCMODE

# ifndef FCNTL_ACCESS_DEFINED
#  define FCNTL_ACCESS_DEFINED
#  define O_RDONLY 0x00
#  define O_WRONLY 0x01
#  define O_RDWR 0x02
# endif // FCNTL_ACCESS_DEFINED

__EXTC

typedef long off_t;
typedef int pid_t;
typedef unsigned int mode_t;

int creat(const char*, mode_t);
int fcntl(int, int, ...);
int open(const char*, int, ...);

__EXTC_END

#endif /* SURGEOS_FCNTL_H */
