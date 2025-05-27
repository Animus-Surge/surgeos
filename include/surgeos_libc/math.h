/**
 * SurgeOS libc math.h
 * Mathematical functions and macros
 */

#ifndef SURGEOS_MATH_H
#define SURGEOS_MATH_H

_EXTC

#include <stdint.h>

typedef float float_t;
typedef double double_t;

#define INFINITY
#define NAN
#define HUGE_VAL 1.0e+300
#define HUGE_VALF 1.0e+300f
#define HUGE_VALL 1.0e+300L

// Mathematical constants
#define PI 3.14159265358979323846
#define E 2.71828182845904523536


// Trig functions

// double precision
double cos(double x);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan(double x);
double atan2(double y, double x);

// float precision
float cosf(float x);
float sinf(float x);
float tanf(float x);
float acosf(float x);
float asinf(float x);
float atanf(float x);
float atan2f(float y, float x);

// long double precision
long double cosl(long double x);
long double sinl(long double x);
long double tanl(long double x);
long double acosl(long double x);
long double asinl(long double x);
long double atanl(long double x);
long double atan2l(long double y, long double x);


// Hyperbolic functions

// double precision
double cosh(double x);
double sinh(double x);
double tanx(double x);
double acosh(double x);
double asinh(double x);
double atanh(double x);

// float precision
float coshf(float x);
float sinhf(float x);
float tanhf(float x);
float acoshf(float x);
float asinhf(float x);
float atanhf(float x);

// long double precision
long double coshl(long double x);
long double sinhl(long double x);
long double tanhl(long double x);
long double acoshl(long double x);
long double asinhl(long double x);
long double atanhf(long double x);


// Exponential/Logarithmic functions
double exp(double x);
float expf(float x);
long double expl(long double x);

double frexp(double x, int* exp);
float frexpf(float x, int* exp);
long double frexpl(long double x, int* exp);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);
long double ldexpl(long double x, int exp);

// Power functions

// Error and gamma functions

// Rounding/remainder functions

// Floating-point manipulation functions

// Min/max/diff functions

// Other functions

#endif /* SURGEOS_MATH_H */
