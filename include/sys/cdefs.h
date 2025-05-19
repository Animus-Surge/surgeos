/**
 * SurgeOS include/sys/cdefs.h
 * sys/cdefs.h
 */

#ifndef SURGEOS_SYS_CDEFS_H
#define SURGEOS_SYS_CDEFS_H

#define __surgeos__ 1

// c++ handling
#ifdef __cplusplus
#define _EXTC extern "C" {
#define _EXTC_END }
#else
#define _EXTC
#define _EXTC_END
#endif

#endif // SURGEOS_SYS_CDEFS_H
