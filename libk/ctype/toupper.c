/**
 * SurgeOS libc ctype/toupper.c
 * `toupper()` implementation
 */

#include <ctype.h>

int toupper(int c)
{
    if (isalpha(c) && islower(c))
        return c - ('a' - 'A');
    return c;
}

