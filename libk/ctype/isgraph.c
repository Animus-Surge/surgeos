/**
 * SurgeOS libc ctype/isgraph.c
 * `isgraph()` implementation
 */

#include <ctype.h>

int isgraph(int c)
{
    return (c >= 0x21 && c <= 0x7E);
}

