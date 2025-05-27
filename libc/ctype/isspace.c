/**
 * SurgeOS libc ctype/isspace.c
 * isspace() implementation
 */

#include <ctype.h>

int isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
            c == '\f' || c == '\r');
}
