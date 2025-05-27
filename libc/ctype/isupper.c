/**
 * SurgeOS libc ctype/isupper.c
 * isupper() implementation
 */

#include <ctype.h>
int isupper(int c)
{
    return (c >= 'A' && c <= 'Z');
}

