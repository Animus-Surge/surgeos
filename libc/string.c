/**
 * SurgeOS libc string.c
 * String definitions
 */

#include <string.h>

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* p1 = (const unsigned char*)s1;
    const unsigned char* p2 = (const unsigned char*)s2;

    for (size_t i = 0; i < n; i++) {
        if(p1[i] > p2[i]) {
            return 1;
        } else if(p1[i] < p2[i]) {
            return -1;
        }
    }
    return 0;
}

void* memcpy(void* __restrict dest, const void* __restrict src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void* memmove(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d < s) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    return dest;
}

void* memset(void* dest, int c, size_t n) {
    unsigned char* d = (unsigned char*)dest;

    for (size_t i = 0; i < n; i++) {
        d[i] = (unsigned char)c;
    }
    return dest;
}

size_t strlen(const char* str) {
    const char* s = str;

    while (*s) {
        s++;
    }
    return (size_t)(s - str);
}
