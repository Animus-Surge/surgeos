/**
 * SurgeOS libc curses.h
 * Curses library header
 */

#ifndef SURGEOS_CURSES_H
#define SURGEOS_CURSES_H

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

__EXTC

typedef unsigned short attr_t;
typedef struct {
  char ch;
  attr_t attr;
  unsigned char color;
} chtype;

typedef struct {
  int x, y;          // Position in the window
  int width, height; // Size of the window
  chtype* buffer;    // Character buffer for the window
  bool is_visible;   // Visibility state of the window
} WINDOW;

#endif // SURGEOS_CURSES_H
