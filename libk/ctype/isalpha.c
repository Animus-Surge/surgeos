/**
 * SurgeOS libc ctype/isalpha.c
 * `isalpha()` implementation
 */

#include <ctype.h>

int isalpha(int c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

