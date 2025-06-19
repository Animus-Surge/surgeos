/**
 * SurgeOS include/sys/cdefs.h
 * sys/cdefs.h
 */

#ifndef SURGEOS_SYS_CDEFS_H
#define SURGEOS_SYS_CDEFS_H

#define __surgeos__ 1

#define __surgeos_public __attribute__((visibility("default")))
#define __surgeos_local __attribute__((visibility("hidden")))

#define __surgeos_noreturn __attribute__((__noreturn__))
#define __surgeos_packed __attribute__((packed))
#define __surgeos_aligned(x) __attribute__((aligned(x)))
#define __surgeos_unused __attribute__((unused))
#define __surgeos_deprecated __attribute__((deprecated))

// c++ handling
#ifdef __cplusplus
#define __EXTC extern "C" {
#define __EXTC_END }
#else
#define __EXTC
#define __EXTC_END
#endif

#endif // SURGEOS_SYS_CDEFS_H
