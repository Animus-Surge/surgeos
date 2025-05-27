/**
 * SurgeOS libc ctype/isprint.c
 * isprint() implementation
 */

#include <ctype.h>

int isprint(int c)
{
    return (c >= 0x20 && c <= 0x7E);
}
