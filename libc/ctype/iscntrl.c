/**
 * SurgeOS libc ctype/iscntrl.c
 * iscntrl() implementation
 */

#include <ctype.h>

int iscntrl(int c)
{
    return (c >= 0 && c <= 037) || (c == 0177);
}
