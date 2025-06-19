/**
 * SurgeOS kernel multiboot.h
 * Multiboot header file
 */

#ifndef SURGEOS_KERNEL_MULTIBOOT_H
#define SURGEOS_KERNEL_MULTIBOOT_H

#include <stdint.h>

#define MB_MAGIC 0x36d76289

#define MB_TAG_END 0
#define MB_TAG_CMDLINE 1
#define MB_TAG_BOOTNAME 2
#define MB_TAG_MODULE 3
#define MB_TAG_BASIC_MEMINFO 4
#define MB_TAG_BOOTDEV 5
#define MB_TAG_MMAP 6
#define MB_TAG_VBE 7
#define MB_TAG_FRAMEBUFFER 8
#define MB_TAG_ELF 9

#define MB_MEM_AVAILABLE 1

struct mb_tag {
  uint32_t type;
  uint32_t size;
};

// 0x06: Memory map
struct mb_mmap_entry {
  uint64_t addr; // Start address of the memory region
  uint64_t len;  // Length of the memory region
  uint32_t type; // Type of the memory region (1: available, 2: reserved, etc.)
  uint32_t zero; // Reserved, must be zero
};

struct mb_tag_mmap {
  uint32_t type; // 6
  uint32_t size;
  uint32_t entry_size;
  uint32_t entry_version;
  struct mb_mmap_entry entries[];
};

struct mb_framebuffer_color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};
struct mb_tag_framebuffer {
  uint32_t type; // 8
  uint32_t size;
  uint64_t fb_addr;
  uint32_t fb_pitch;
  uint32_t fb_width;
  uint32_t fb_height;
  uint8_t fb_bpp; // Bits per pixel
  uint8_t fb_type; // 0: indexed, 1: rgb, 2: efi
  uint16_t fb_reserved; // Reserved, must be zero
  
  union {
    struct {
      uint16_t framebuffer_num_palette_colors; // Number of colors in the palette
      struct mb_framebuffer_color* palette; // Pointer to the color palette
    } indexed;

    struct {
      uint8_t framebuffer_red_field_position;
      uint8_t framebuffer_red_mask_size;
      uint8_t framebuffer_green_field_position;
      uint8_t framebuffer_green_mask_size;
      uint8_t framebuffer_blue_field_position;
      uint8_t framebuffer_blue_mask_size;
    } rgb;
  };
};

struct mb_info {
  uint32_t size; // Size of the multiboot information structure
  uint32_t reserved; // Zero
  uint8_t tags[];
};

#endif // SURGEOS_KERNEL_MULTIBOOT_H
