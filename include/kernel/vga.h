/**
 * SurgeOS kernel include/vga.h
 * VGA function declarations
 */

#ifndef SURGEOS_VGA_H
#define SURGEOS_VGA_H

#include <kernel/multiboot.h>

#include <stdint.h>
#include <stddef.h>

#define RGB(r, g, b) (((r)) | ((g) << 8) | (b << 16)) // RGB macro for color conversion

#define FB_VIRT_ADDR 0xE0000000

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

enum vga_type {
  VGA_TYPE_INDEXED = 0, // Indexed color mode
  VGA_TYPE_RGB = 1,     // RGB color mode
  VGA_TYPE_EFI = 2      // EFI framebuffer
};

typedef struct {
  void* address; // Framebuffer address
  uint32_t width, height; // Framebuffer dimensions
  uint32_t pitch; // Number of bytes per row
  uint8_t bpp; // Bits per pixel
  enum vga_type type; // Framebuffer type

  // RGB color mode specific
  uint8_t red_mask, green_mask, blue_mask; // Masks for RGB components
  uint8_t red_pos, green_pos, blue_pos; // Bit positions for RGB components

  // Indexed color mode specific
  uint32_t palette_size;
  struct mb_framebuffer_color* palette; // Pointer to color palette
} framebuffer_t;
  

// Common functions
void init_fallback_vga(void);
int vga_init(struct mb_tag_framebuffer*);
void vga_clear(void);

void vga_drawpx(size_t, size_t, uint32_t);

// Text drawing functions
void vga_drawc(char, size_t, size_t, uint32_t);
void vga_draws(const char*, size_t, size_t, uint32_t);

// Text mode functions
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

// Direct framebuffer modification
void vga_virt_fb_addr(void);

#endif // SURGEOS_VGA_H
