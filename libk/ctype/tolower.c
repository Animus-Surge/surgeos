/**
 * SurgeOS libc ctype/tolower.c
 * `tolower()` implementation
 */

#include <ctype.h>

int tolower(int c)
{
    if (isalpha(c) && isupper(c))
        return c + ('a' - 'A');
    return c;
}

