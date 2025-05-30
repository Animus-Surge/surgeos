/**
 * SurgeOS include/stdlib.h
 * stdlib.h
 */

#ifndef SURGEOS_STDLIB_H
#define SURGEOS_STDLIB_H

#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stddef.h>
#include <limits.h>
#include <math.h>

#include <stdnoreturn.h>

__EXTC

#define WNOHANG 0x01
#define WUNTRACED 0x02
#define WEXITSTATUS(status) (((status) & 0xFF00) >> 8)
#define WIFEXITED(status) (((status) & 0xFF) == 0)
#define WIFSIGNALED(status) (((status) & 0xFF) != 0 && !WIFEXITED(status))
#define WIFSTOPPED(status) (((status) & 0xFF) == 0x7F)
#define WSTOPSIG(status) ((status) & 0x7F)
#define WTERMSIG(status) ((status) & 0x7F)

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define NULL ((void*)0)

#define RAND_MAX
#define MB_CUR_MAX 0x10FFFF

typedef struct {
    int quot;  // quotient
    int rem;   // remainder
} div_t;

typedef struct {
    long quot;  // quotient
    long rem;   // remainder
} ldiv_t;

// exit functions
noreturn void abort(void);
int atexit(void (*)(void));
void exit(int);

// string conversion functions
long a64l(const char*);
double atof(const char*);
int atoi(const char*);
long atol(const char*);
char* ecvt(double, int, int*, int*);
char* fcvt(double, int, int*, int*);
char* gcvt(double, int, char*);
char* l64a(long);
double strtod(const char*, char**);
long strtol(const char*, char**, int);
unsigned long strtoul(const char*, char**, int);

// random number generation functions
double drand48(void);
double erand48(unsigned short[3]);
long jrand48(unsigned short[3]);
long lrand48(void);
long mrand48(void);
long nrand48(unsigned short[3]);
int rand(void);
int rand_r(unsigned int*);
long random(void);
unsigned short seed48(unsigned short[3]);
void srand(unsigned int);
void srand48(long);
void srandom(unsigned int);

// environment functions
char* getenv(const char*);
int putenv(char*);

// process control functions
int system(const char*);

// memory management functions
void* calloc(size_t, size_t);
void free(void*);
void* malloc(size_t);
void* realloc(void*, size_t);
void* valloc(size_t); // deprecated, use malloc instead

// searching and sorting functions
void* bsearch(const void*, const void*, size_t, size_t, int(*)(const void*, const void*));
void qsort(void*, size_t, size_t, int(*)(const void*, const void*));

// string manipulation functions
size_t mbstowcs(wchar_t*, const char*, size_t);
size_t wcstombs(char*, const wchar_t*, size_t);
size_t mbsrtowcs(wchar_t*, const char**, size_t, mbstate_t*);
size_t wcsrtombs(char*, const wchar_t**, size_t, mbstate_t*);

// math functions

// utility functions

__EXTC_END

#endif // SURGEOS_STDLIB_H

