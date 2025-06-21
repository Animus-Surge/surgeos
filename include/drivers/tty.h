/**
 * SurgeOS drivers tty.h
 * tty driver header file
 */

#ifndef SURGEOS_DRIVER_TTY_H
#define SURGEOS_DRIVER_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// TTY driver structure
typedef struct {
  // Terminal dimensions and cursor position
  size_t width;
  size_t height;
  size_t cursor_x;
  size_t cursor_y;

  // Buffers
  char cmd_buffer[512]; // Command buffer for input
  size_t buf_pos;

  // Flags and state
  bool initialized;
  bool echo_enabled;
  bool cmd_ready; // Indicates if a command is ready to be processed
  bool input_ready;
  bool new_line_ready; // Indicates if we're ready for a new input line

  // Colors
  uint32_t fg;
  uint32_t bg;
} tty_t;

void tty_init(void);
void tty_loop(void);

// Output functions
void tty_write(const char*, size_t);
void tty_writechar(char);
void tty_setchar(char, size_t, size_t, uint32_t, uint32_t);
void tty_clear(void);

// Cursor functions
void tty_set_cursor(size_t, size_t);
size_t tty_get_cursor_x(void);
size_t tty_get_cursor_y(void);

// Color functions
void tty_set_fg_color(uint32_t);
uint32_t tty_get_fg_color(void);
void tty_set_bg_color(uint32_t);
uint32_t tty_get_bg_color(void);


#endif // SURGEOS_DRIVER_TTY_H
