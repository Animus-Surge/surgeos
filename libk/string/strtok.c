/**
 * SurgeOS libk strtok.c
 * `strtok()` implementation
 */

#include <stddef.h>
#include <string.h>

char* strtok(char* str, const char* delim) {
  static char next[256];
  static size_t pos = 0;

  size_t len = strlen(str);

  if (str != NULL) {
    pos = 0;
    strncpy(next, str, sizeof(next) - 1);
    next[len] = '\0';
  }
  if (next[pos] == '\0') {
    return NULL; // No more tokens
  }

  while (next[pos] != '\0') {
    const char* d = delim;
    int is_delim = 0;

    while (*d != '\0') {
      if (next[pos] == *d) {
        is_delim = 1;
        break;
      }
      d++;
    }
    if (!is_delim) {
      break;
    }
    pos++;
  }

  if (next[pos] == '\0') {
    return NULL; // No more tokens
  }

  size_t start = pos;

  while(next[pos] != '\0') {
    const char* d = delim;
    int is_delim = 0;

    while (*d != '\0') {
      if (next[pos] == *d) {
        is_delim = 1;
        next[pos++] = '\0'; // Null-terminate the token
        break;
      }
      d++;
    }
    if (is_delim) {
      break; // Found a delimiter, stop here
    }
    pos++;
  }

  return &next[start]; // Return the token
}

    


