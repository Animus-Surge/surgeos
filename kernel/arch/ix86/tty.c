/**
 * SurgeOS kernel tty.c
 * TTY driver
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/vga.h>

// Memory position
static uint16_t* tty_mem = (uint16_t*)TTY_MEM_POS;

// Cursor position
static int cursor_row;
static int cursor_col;

// Terminal color
static uint8_t color;

// Helper functions
void handle_scrolldown(void) {
  // Scroll the screen up by one line
  memmove(tty_mem, tty_mem + TTY_WIDTH, (TTY_HEIGHT - 1) * TTY_WIDTH * sizeof(uint16_t));
  memset(tty_mem + (TTY_HEIGHT - 1) * TTY_WIDTH, 0, TTY_WIDTH * sizeof(uint16_t));
}

// Cursor functions
void term_set_cursor(int x, int y) {
  cursor_col = x;
  cursor_row = y;
}
void term_get_cursor(int* x, int* y) {
  *x = cursor_col;
  *y = cursor_row;
}

// Color functions
void term_set_color(uint8_t c) {
  color = c;
}
uint8_t term_get_color(void) {
  return color;
}
void term_set_bg_color(uint8_t c) {
  color = (color & 0x0F) | (c << 4);
}
uint8_t term_get_bg_color(void) {
  return (color >> 4) & 0x0F;
}
void term_set_fg_color(uint8_t c) {
  color = (color & 0xF0) | (c & 0x0F);
}
uint8_t term_get_fg_color(void) {
  return color & 0x0F;
}

// Initialization functions
void term_init(void) {
  color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  cursor_row = 0;
  cursor_col = 0;
  term_clear();
}

void term_clear(void) {
  memset(tty_mem, 0, TTY_WIDTH * TTY_HEIGHT * sizeof(uint16_t));
  for (int i = 0; i < TTY_WIDTH * TTY_HEIGHT; i++) {
    tty_mem[i] = vga_entry(' ', color);
  }
  cursor_row = 0;
  cursor_col = 0;
}

// Writer functions
void term_putchar(char c) { //TODO: escape sequences
  if (c == '\n') {
    if (++cursor_row >= TTY_HEIGHT) {
      handle_scrolldown();
      cursor_row = TTY_HEIGHT - 1;
    }
    cursor_col = 0;
    return;
  } else if (c == '\r') {
    cursor_col = 0;
    return;
  } else if (c == 8) { // Backspace
    if (cursor_col > 0) {
      cursor_col--;
    }
    term_putchar_pos(' ', cursor_col, cursor_row); // Clear the character
    return;
  }

  else if (c < 32 || c > 126) { // Ignore non-printable characters
    return;
  }

  term_putchar_pos(c, cursor_col, cursor_row);
  if(++cursor_col >= TTY_WIDTH) {
    cursor_col = 0;
    if (++cursor_row >= TTY_HEIGHT) {
      handle_scrolldown();
      cursor_row = TTY_HEIGHT - 1;
    }
  }
}

void term_putchar_pos(char c, int x, int y) {
  if (x < 0 || x >= TTY_WIDTH || y < 0 || y >= TTY_HEIGHT) {
    return;
  }
  tty_mem[y * TTY_WIDTH + x] = vga_entry(c, color);
}

void term_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    term_putchar(data[i]);
  }
}

void term_writestr(const char* data) {
  size_t len = strlen(data);
  term_write(data, len);
}

