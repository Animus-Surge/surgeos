/**
 * SurgeOS libc ctype/isxdigit.c
 * `isxdigit()` implementation
 */

#include <ctype.h>
int isxdigit(int c)
{
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'));
}

