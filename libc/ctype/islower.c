/**
 * SurgeOS libc ctype/islower.c
 * `islower()` implementation
 */

#include <ctype.h>

int islower(int c)
{
    return (c >= 'a' && c <= 'z');
}

