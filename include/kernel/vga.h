/**
 * SurgeOS kernel include/vga.h
 * VGA function declarations
 */

#ifndef SURGEOS_VGA_H
#define SURGEOS_VGA_H

#include <stdint.h>
#include <stddef.h>

#define VGA_TEXT_MODE_ADDRESS 0xb8000
#define VGA_RASTER_MODE_ADDRESS 0xa0000

#define VGA_MODE_UNKNOWN 0
#define VGA_MODE_RASTER 1
#define VGA_MODE_TEXT 2

#define VGA_FLAG_USE_DAC 0x1

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} rgbcolor_t;

enum vga_color {
  // 16 Color Mode
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
  
  // 256 Color Mode (XTerm color map)
  // TODO: add friendly names
};

// Common functions
int vga_init(uint8_t);
void vga_clear(void);

// Text mode functions
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

#endif // SURGEOS_VGA_H
