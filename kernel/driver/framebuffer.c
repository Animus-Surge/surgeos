/**
 * SurgeOS kernel driver/vga.c
 * Graphics mode vga driver implementation
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <kernel/memory.h>

#include <drivers/framebuffer.h>
#include <drivers/serial.h>

#include <_font.h>

#define SCALE_SIZE 1

static framebuffer_t fb = {0};

/**
 * @brief Initialize VGA graphics mode given framebuffer information.
 *
 * This function initializes the VGA graphics mode using the provided framebuffer
 * information. If the framebuffer is NULL or invalid, it falls back to text mode.
 *
 * @param fb (struct mb_tag_framebuffer*) Pointer to the framebuffer information.
 *
 * @return int Returns 0 on success, or -1 if the framebuffer is invalid.
 */
int framebuffer_init(struct mb_tag_framebuffer* mb_fb) {
  if (!mb_fb) {
    serial_writes("VGA: No framebuffer found, falling back to text mode\n");
    return -1;
  }

  serial_writes("VGA: Initializing graphics mode\n");
  serial_writes("VGA: Framebuffer type: ");
  switch (mb_fb->type) {
    case 0: serial_writes("Indexed color mode\n"); break;
    case 8:
    case 1: serial_writes("RGB mode\n"); break;
    case 2: serial_writes("EFI mode\n"); break;
    default: serial_printf("Unknown type %d, falling back to text mode\n", mb_fb->type); break;
  }
  serial_printf("VGA: Framebuffer address: 0x%X\n", mb_fb->fb_addr);
  serial_printf("VGA: Framebuffer dimensions: %dx%d\n", mb_fb->fb_width, mb_fb->fb_height);
  serial_printf("VGA: Framebuffer pitch: %d bytes\n", mb_fb->fb_pitch);
  serial_printf("VGA: Framebuffer bpp: %d\n", mb_fb->fb_bpp);

  // Initialize the framebuffer
  
  // Common values
  fb.address = (void*)(uintptr_t)mb_fb->fb_addr;
  fb.width = mb_fb->fb_width;
  fb.height = mb_fb->fb_height;
  fb.pitch = mb_fb->fb_pitch;
  fb.bpp = mb_fb->fb_bpp;

  switch (mb_fb->type) {
    case 0: // Indexed color mode
      fb.type = VGA_TYPE_INDEXED;
      fb.palette_size = mb_fb->indexed.framebuffer_num_palette_colors;
      fb.palette = mb_fb->indexed.palette;

      serial_printf("VGA: Indexed color mode with %d colors\n", fb.palette_size);
      serial_printf("VGA: Palette address: 0x%X\n", (uintptr_t)fb.palette);
      break;
    case 1: // RGB mode
    case 8:
      fb.type = VGA_TYPE_RGB;
      fb.red_mask = mb_fb->rgb.framebuffer_red_mask_size;
      fb.green_mask = mb_fb->rgb.framebuffer_green_mask_size;
      fb.blue_mask = mb_fb->rgb.framebuffer_blue_mask_size;
      fb.red_pos = mb_fb->rgb.framebuffer_red_field_position;
      fb.green_pos = mb_fb->rgb.framebuffer_green_field_position;
      fb.blue_pos = mb_fb->rgb.framebuffer_blue_field_position;

      serial_printf("VGA: RGB mode with masks: R=0x%X, G=0x%X, B=0x%X\n",
                   fb.red_mask, fb.green_mask, fb.blue_mask);
      serial_printf("VGA: RGB positions: R=%d, G=%d, B=%d\n",
                   fb.red_pos, fb.green_pos, fb.blue_pos);
      break;
    case 2: // EFI mode
      fb.type = VGA_TYPE_EFI;
      // EFI mode does not require additional setup
      break;
    default:
      return -1;
  }

  return 0;
}

void framebuffer_drawpx(size_t x, size_t y, uint32_t color) {
  if (fb.type == VGA_TYPE_EFI) return;

  size_t scaled_x = x * SCALE_SIZE;
  size_t scaled_y = y * SCALE_SIZE;

  if (scaled_x + 1 >= fb.width || scaled_y + 1 >= fb.height) {
    return; // Out of bounds
  }

  // Draw a 2x2 block
  for (size_t dy = 0; dy < SCALE_SIZE; dy++) {
    for (size_t dx = 0; dx < SCALE_SIZE; dx++) {
      uint8_t* addr = (uint8_t*)fb.address +
                      (scaled_y + dy) * fb.pitch +
                      (scaled_x + dx) * (fb.bpp / 8);

      switch (fb.type) {
        case VGA_TYPE_RGB:
          addr[0] = (uint8_t)((color >> fb.red_pos) & 0xFF);
          addr[1] = (uint8_t)((color >> fb.green_pos) & 0xFF);
          addr[2] = (uint8_t)((color >> fb.blue_pos) & 0xFF);
          break;

        case VGA_TYPE_INDEXED:
          addr[0] = (uint8_t)color;
          break;

        default:
          return;
      }
    }
  }
}

/**
 * @brief Clear the VGA framebuffer.
 *
 * This function clears the entire framebuffer by filling it with spaces
 * and setting the default attribute (light gray on black).
 */
void framebuffer_clear(void) {
  uint8_t* address = (uint8_t*)fb.address;
  size_t bpp = fb.bpp / 8; // Bytes per pixel

  switch(fb.type) {
    case VGA_TYPE_RGB:
    case VGA_TYPE_INDEXED:
      if(fb.pitch == fb.width * bpp) {
        memset(address, 0x00, fb.width * fb.height); // Clear the entire framebuffer
      } else {
        for (size_t y = 0; y < fb.height; y++) {
          memset(address + y * fb.pitch, 0x00, fb.width * bpp);
        }
      }
      break;
    case VGA_TYPE_EFI: // Text mode
      for (size_t x = 0; x < fb.width; x++) {
        for (size_t y = 0; y < fb.height; y++) {
          size_t index = (y * fb.width + x) * 2;
          ((char*)fb.address)[index] = ' '; // Clear character
          ((char*)fb.address)[index + 1] = 0x07; // Default attribute (light gray on black)
        }
      }
      break;
    default:
      return; // Unsupported type, do nothing
  }
}

void framebuffer_drawc(char c, size_t x, size_t y, uint32_t fg, uint32_t bg) {
  // TODO: support raster modes
  
  if (x >= fb.width || y >= fb.height) {
    return; // Out of bounds
  }

  uint8_t* address = (uint8_t*)fb.address;

  switch(fb.type) {
    case VGA_TYPE_INDEXED:
    case VGA_TYPE_RGB:
      uint8_t* character = (uint8_t*)&font_data[(unsigned char)c];
      for (size_t row = 0; row < 8; row++) {
        for (size_t col = 0; col < 8; col++) {
          size_t px_x = x + col;
          size_t px_y = y + row;
          if (character[row] & (1 << (7 - col))) { // Check if pixel is set
            if (px_x < fb.width && px_y < fb.height) {
              framebuffer_drawpx(px_x, px_y, fg);
            }
          } else {
            // Draw background pixel
            if (px_x < fb.width && px_y < fb.height) {
              framebuffer_drawpx(px_x, px_y, bg);
            }
          }
        }
      }
      break;
    case VGA_TYPE_EFI: // Text mode
      size_t index = (y * fb.width + x) * 2;
      ((char*)fb.address)[index] = c; // Set character
      ((char*)fb.address)[index + 1] = (uint8_t)fg; // Set attribute
      break;
  }
}

void framebuffer_draws(const char* str, size_t x, size_t y, uint32_t fg, uint32_t bg) {
  if (!str || x >= fb.width || y >= fb.height) {
    return; // Invalid string or out of bounds
  }

  size_t len = strlen(str);
  for (size_t i = 0; i < len; i++) {
    framebuffer_drawc(str[i], x + (i * 8), y, fg, bg);
  }
}

/**
 * @brief Map the framebuffer to virtual memory.
 *
 * This function maps the physical framebuffer address to a virtual address
 * for direct access in the kernel. It uses a predefined virtual address
 * and maps the physical framebuffer address to it.
 */
void framebuffer_virt_fb_addr(void) {
  serial_printf("VGA: Physical framebuffer address: 0x%X\n", (uintptr_t)fb.address);

  uintptr_t fb_phys = (uintptr_t)fb.address;
  size_t fb_size = fb.width * fb.height * (fb.bpp / 8);
  uintptr_t fb_virt = FB_VIRT_ADDR;

  serial_printf("VGA: Virtual framebuffer address: 0x%X\n", fb_virt);
  serial_writes("VGA: Mapping framebuffer to virtual memory\n");

  if (!vmem_map_range(fb_virt, fb_phys, fb_size, PAGE_PRESENT | PAGE_RW)) {
    serial_printf("VGA: Failed to map framebuffer to virtual memory at 0x%X\n", fb_virt);
    panic("Failed to map framebuffer to virtual memory");
  } else {
    serial_printf("VGA: Framebuffer mapped to virtual memory at 0x%X\n", fb_virt);
  }

  fb.address = (void*)(fb_virt + (fb_phys & 0xFFF)); // Adjust virtual address to match physical offset
}

/**
 * @brief Get the width of the framebuffer
 * 
 * Is affected by scaling size
 *
 * @return The width of the frameebuffer
 */
uint32_t framebuffer_get_width(void) {
  return fb.width / SCALE_SIZE;
}

/**
 * @brief Get the height of the framebuffer
 *
 * Is affected by scaling size
 *
 * @return The height of the framebuffer
 */
uint32_t framebuffer_get_height(void) {
  return fb.height / SCALE_SIZE;
}


