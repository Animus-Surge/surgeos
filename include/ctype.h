/**
 * SurgeOS libc ctype.h
 * Character classification functions
 */

#ifndef SURGEOS_CTYPE_H
#define SURGEOS_CTYPE_H

#include <stdint.h>

int isalnum(int c);
int isalpha(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);

#endif /* SURGEOS_CTYPE_H */
