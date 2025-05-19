/**
 * SurgeOS libc string/memcmp.c
 * memcmp() implementation
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
