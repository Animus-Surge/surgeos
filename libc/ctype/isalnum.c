/**
 * SurgeOS libc ctype/isalnum.c
 * `isalnum()` implementation
 */

#include <ctype.h>

int isalnum(int c)
{
    return (isalpha(c) || isdigit(c));
}

