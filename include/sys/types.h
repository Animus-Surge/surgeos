/**
 * SurgeOS sys/types.h
 * Standard types
 */

#ifndef SURGEOS_SYS_TYPES_H
#define SURGEOS_SYS_TYPES_H

#include <sys/cdefs.h>

__EXTC

# ifndef SIZE_T_DEFINED
#  define SIZE_T_DEFINED
typedef unsigned long size_t;
# endif

# ifndef OFF_T_DEFINED
#  define OFF_T_DEFINED
typedef long off_t;
# endif

# ifndef MODE_T_DEFINED
#  define MODE_T_DEFINED
typedef unsigned int mode_t;
# endif

# ifndef ID_T_DEFINED
#  define ID_T_DEFINED
typedef int id_t;
# endif

# ifndef PID_T_DEFINED
#  define PID_T_DEFINED
typedef int pid_t;
# endif

# ifndef UID_T_DEFINED
#  define PID_T_DEFINED
typedef unsigned long uid_t;
# endif

# ifndef GID_T_DEFINED
#  define GID_T_DEFINED
typedef unsigned long gid_t;
# endif


__EXTC_END

#endif /* SURGEOS_SYS_TYPES_H */
