/**
 * SurgeOS sys/types.h
 * Standard types
 */

#ifndef SURGEOS_SYS_TYPES_H
#define SURGEOS_SYS_TYPES_H

#include <sys/cdefs.h>

__EXTC

// Missing:
//pthread_attr_t
//pthread_cond_t
//pthread_condattr_t
//pthread_key_t
//pthread_mutex_t
//pthread_once_t
//pthread_rwlock_t
//pthread_rwlockattr_t
//pthread_t
//suseconds_t
//useconds_t

// File block counts
# ifndef BLKCNT_T_DEFINED
#  define BLKCNT_T_DEFINED
typedef long blkcnt_t;
# endif

// File block size
# ifndef BLKSIZE_T_DEFINED
#  define BLKSIZE_T_DEFINED
typedef long blksize_t;
# endif

// System times
# ifndef CLOCK_T_DEFINED
#  define CLOCK_T_DEFINED
typedef long clock_t;
# endif

// Clock ID
# ifndef CLOCKID_T_DEFINED
#  define CLOCKID_T_DEFINED
typedef int clockid_t;
# endif

// Device ID
# ifndef DEV_T_DEFINED
#  define DEV_T_DEFINED
typedef unsigned long dev_t;
# endif

// FS block count
# ifndef FSBLKCNT_T_DEFINED
#  define FSBLKCNT_T_DEFINED
typedef unsigned long fsblkcnt_t;
# endif

// FS file count
# ifndef FSFILCNT_T_DEFINED
#  define FSFILCNT_T_DEFINED
typedef unsigned long fsfilcnt_t;
# endif

// Group ID
# ifndef GID_T_DEFINED
#  define GID_T_DEFINED
typedef unsigned long gid_t;
# endif

// Generic ID type
# ifndef ID_T_DEFINED
#  define ID_T_DEFINED
typedef int id_t;
# endif

// File serial number
# ifndef INO_T_DEFINED
#  define INO_T_DEFINED
typedef unsigned long ino_t;
# endif

// Interprocess communication key
# ifndef KEY_T_DEFINED
#  define KEY_T_DEFINED
typedef int key_t;
# endif

// File attributes
# ifndef MODE_T_DEFINED
#  define MODE_T_DEFINED
typedef unsigned int mode_t;
# endif

// Link counts
# ifndef NLINK_T_DEFINED
#  define NLINK_T_DEFINED
typedef unsigned long nlink_t;
# endif

// File sizes
# ifndef OFF_T_DEFINED
#  define OFF_T_DEFINED
typedef long off_t;
# endif

// Process ID
# ifndef PID_T_DEFINED
#  define PID_T_DEFINED
typedef int pid_t;
# endif

// Object size
# ifndef SIZE_T_DEFINED
#  define SIZE_T_DEFINED
typedef unsigned long size_t;
# endif

// Byte count for errors
# ifndef SSIZE_T_DEFINED
#  define SSIZE_T_DEFINED
typedef unsigned long ssize_t;
# endif

// Time in seconds
# ifndef TIME_T_DEFINED
#  define TIME_T_DEFINED
typedef long time_t;
# endif

// Timer ID
# ifndef TIMER_T_DEFINED
#  define TIMER_T_DEFINED
typedef int timer_t;
# endif

// User ID
# ifndef UID_T_DEFINED
#  define PID_T_DEFINED
typedef unsigned long uid_t;
# endif

__EXTC_END

#endif /* SURGEOS_SYS_TYPES_H */
