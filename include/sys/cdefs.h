/**
 * SurgeOS include/sys/cdefs.h
 * sys/cdefs.h
 */

#ifndef SURGEOS_SYS_CDEFS_H
#define SURGEOS_SYS_CDEFS_H

#define __surgeos__ 1

#define __surgeos_public __attribute__((visibility("default")))
#define __surgeos_local __attribute__((visibility("hidden")))

// c++ handling
#ifdef __cplusplus
#define __EXTC extern "C" {
#define __EXTC_END }
#else
#define __EXTC
#define __EXTC_END
#endif

#endif // SURGEOS_SYS_CDEFS_H
