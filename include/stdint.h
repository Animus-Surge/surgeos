/**
 * SurgeOS libc stdint.h
 * Standard integer types
 */

#ifndef SURGEOS_STDINT_H
#define SURGEOS_STDINT_H

// Integer size macros
#define INTMAX_MIN 
#define INTMAX_MAX 
#define UINTMAX_MAX 

#define INT8_MIN -128
#define INT16_MIN -32_768
#define INT32_MIN -2_147_483_648
#define INT64_MIN -9_223_372_036_854_775_808

#define INT8_MAX 127
#define INT16_MAX 32_767
#define INT32_MAX 2_147_483_647
#define INT64_MAX 9_223_372_036_854_775_807

#define UINT8_MAX 255
#define UINT16_MAX 65_535
#define UINT32_MAX 4_294_967_295
#define UINT64_MAX 18_446_744_073_709_551_615

#define INTMAX_C(x)
#define UINTMAX_C(x)
#define INT8_C(x) ((int8_t)x)
#define INT16_C(x) ((int16_t)x)
#define INT32_C(x) x##L
#define INT64_C(x) x##LL
#define UINT8_C(x) x##U
#define UINT16_C(x) x##U
#define UINT32_C(x) x##UL
#define UINT64_C(x) x##ULL

// Unsigned types

typedef unsigned long long int uintmax_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long int uint64_t;
typedef unsigned int* uintptr_t;

// Signed types

typedef long long int intmax_t;
typedef char int8_t;
typedef short int int16_t;
typedef long int int32_t;
typedef long long int int64_t;
typedef int* intptr_t;

#endif
