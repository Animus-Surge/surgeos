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
int framebuffer_init(struct mb_tag_framebuffer*);
void framebuffer_clear(void);

void framebuffer_drawpx(size_t, size_t, uint32_t);

// Text drawing functions
void framebuffer_drawc(char, size_t, size_t, uint32_t, uint32_t);
void framebuffer_draws(const char*, size_t, size_t, uint32_t, uint32_t);

// Direct framebuffer modification
void framebuffer_virt_fb_addr(void);

// Direct framebuffer accessing functions
uint32_t framebuffer_get_width(void);
uint32_t framebuffer_get_height(void);

#endif // SURGEOS_VGA_H
