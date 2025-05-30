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

#define INFINITY 1.0f / 0.0f
#define NAN 0.0f / 0.0f
#define HUGE_VAL 1.0e+300f
#define MAXFLOAT 3.402823466e+38f

// Mathematical constants
#define M_PI 3.14159265358979323846d
#define M_PI_2 1.57079632679489661923d
#define M_PI_4 0.78539816339744830962d
#define M_1_PI 0.31830988618379067154d
#define M_2_PI 0.63661977236758134308d
#define M_2_SQRTPI 1.12837916709551257390d
#define M_SQRT2 1.41421356237309504880d
#define M_SQRT1_2 0.70710678118654752440d

#define M_E 2.71828182845904523536d
#define M_LOG2E 1.44269504088896340736d
#define M_LOG10E 0.43429448190325182765d
#define M_LN2 0.69314718055994530942d
#define M_LN10 2.30258509299404568402d

// Trig functions

// double precision
double cos(double);
double sin(double);
double tan(double);
double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);

// Hyperbolic functions
double cosh(double x);
double sinh(double);
double tanx(double);
double acosh(double);
double asinh(double);
double atanh(double);

// Exponential/Logarithmic functions
double exp(double);
double expm1(double);
double frexp(double, int*);
int ilogb(double);
double ldexp(double, int);
double log(double);
double log10(double);
double log1p(double);

// Power functions
double pow(double, double);
double sqrt(double);
double cbrt(double);

// Error and gamma functions
double erf(double);
double erfc(double);
double lgamma(double);

// Rounding/remainder functions
double ceil(double);
double fabs(double);
double floor(double);
double fmod(double, double);
double remainder(double, double);

// Floating-point manipulation functions

// Min/max/diff functions

// Misc arithmetic functions
double modf(double, double);

// Other functions
int isnan(double);
double hypot(double, double);
double y0(double);
double y1(double);
double yn(int, double);
double j0(double);
double j1(double);
double jn(int, double);
double nextafter(double, double);
double rint(double);
double scalb(double, double);

#endif /* SURGEOS_MATH_H */
