/**
 * SurgeOS kernel include/tty.h
 * TTY driver declarations
 */

#ifndef SURGEOS_TTY_H
#define SURGEOS_TTY_H

#define TTY_WIDTH 80
#define TTY_HEIGHT 25
#define TTY_MEM_POS 0xB8000

#include <stddef.h>
#include <stdint.h>

// Initialization functions
void term_init(void);
void term_clear(void);

// Cursor functions
void term_set_cursor(int x, int y);
void term_get_cursor(int* x, int* y);

// Color functions
void term_set_color(uint8_t color);
uint8_t term_get_color(void);
void term_set_bg_color(uint8_t color);
uint8_t term_get_bg_color(void);
void term_set_fg_color(uint8_t color);
uint8_t term_get_fg_color(void);

// Writer functions
void term_putchar(char c);
void term_putchar_pos(char c, int x, int y);
void term_write(const char* data, size_t size);
void term_writestr(const char* data);

#endif
