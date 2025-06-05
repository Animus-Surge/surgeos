/**
 * SurgeOS libc ctype/isdigit.c
 * `isdigit()` implementation
 */

#include <ctype.h>

int isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

