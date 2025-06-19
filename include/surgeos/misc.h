/**
 * SurgeOS misc.h
 * Miscellaneous macros and functions, helpers, etc.
 */

#ifndef SURGEOS_MISC_H
#define SURGEOS_MISC_H

// C++ extern "C" block
#ifdef __cplusplus
#define __CPP_EXTERN_BEGIN extern "C" {
#define __CPP_EXTERN_END }
#else
#define __CPP_EXTERN_BEGIN
#define __CPP_EXTERN_END
#endif // __cplusplus

// Attribute macros
#define SURGEOS_PACKED __attribute__((packed))
#define SURGEOS_NORETURN __attribute__((noreturn))
#define SURGEOS_UNUSED __attribute__((unused))
#define SURGEOS_ALIGNED(x) __attribute__((aligned(x)))

// Visibility macros
#define SURGEOS_PUBLIC __attribute__((visibility("default")))
#define SURGEOS_PRIVATE __attribute__((visibility("hidden")))

// Inline assembly macros
#define SURGEOS_ASM_INLINE asm volatile

#endif // SURGEOS_MISC_H
