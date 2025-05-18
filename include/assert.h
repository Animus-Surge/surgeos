/**
 * SurgeOS libc assert.h
 * Diagnostic assertion macros
 */

#ifndef SURGEOS_ASSERT_H
#define SURGEOS_ASSERT_H

#ifdef NDEBUG
#define assert(x) ((void)0)
#else
#define assert(x) \
    ((x) ? (void)0 : __assert_fail(#x, __FILE__, __LINE__, __PRETTY_FUNCTION__))
#endif /* NDEBUG */


void __assert_fail(const char *assertion, const char *file, unsigned int line,
                   const char *function);

#endif /* SURGEOS_ASSERT_H */
