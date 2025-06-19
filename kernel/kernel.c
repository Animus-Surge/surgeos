/**
 * SurgeOS kernel.c
 * Kernel main file
 */

#include <kernel/kernel.h>
#include <kernel/multiboot.h>
#include <kernel/memory.h>
#include <kernel/vga.h>
#include <kernel/driver/serial.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline uint32_t align_up(uint32_t value, uint32_t alignment) {
  return (value + alignment - 1) & ~(alignment - 1);
}

/**
 * @brief Kernel main function
 *
 * This function initializes the kernel and sets up the enviroment. It then
 * proceeds to call the long mode jump logic, which will switch the CPU
 * to 32 bit protected mode and then long jump into the actual operating
 * system entry point.
 *
 * @param magic (uint32_t) the magic number passed by the bootloader
 * @param mb_info (void*) the multiboot information structure address
 *
 * @return void
 */
void kernel_init(uint32_t magic, void* mb_info) {

  // Initialize serial driver
  serial_init();
  serial_writes("SurgeOS kernel v1.3.0\n");

  // Initialize interrupts
  init_idt();
  serial_writes("ISR: Interrupts initialized.\n");

  // Determine if magic number is valid
  if (magic != MB_MAGIC) {
    serial_printf("Invalid magic number: 0x%X\n", magic);
    panic("Invalid magic number");
  }

  // Start walking through the multiboot information structure
  struct mb_info* mb = (struct mb_info*)mb_info;
  struct mb_tag* tag = (struct mb_tag*)mb->tags;

  // Empty structure pointers
  struct mb_tag_mmap* mmap = NULL;
  struct mb_tag_framebuffer* framebuffer = NULL;

  while (tag->type != 0) {
    switch (tag->type) {
      case MB_TAG_MMAP:
        mmap = (struct mb_tag_mmap*)tag;
        serial_writes("Multiboot: Memory map found\n");
        break;
      case MB_TAG_FRAMEBUFFER:
        framebuffer = (struct mb_tag_framebuffer*)tag;
        serial_writes("Multiboot: Framebuffer found\n");
        break;
      default:
        // Ignore for now
        serial_printf("Multiboot: Unknown tag type %d found\n", tag->type);
        break;
    }

    // Move to the next tag
    tag = (struct mb_tag*)((uintptr_t)tag + align_up(tag->size, 8));
  }

  // Initialize physical memory
  if (mmap) {
    mem_init(mmap);
  } else {
    panic("No memory map found");
  }

  // Initialize framebuffer
  if (framebuffer) {
    if (vga_init(framebuffer) != 0) {
      panic("Failed to initialize framebuffer");
    }

    // Mark framebuffer memory as used
    mem_mark_range((uintptr_t)framebuffer->fb_addr,
                     (uintptr_t)framebuffer->fb_addr + 
                     (framebuffer->fb_width * framebuffer->fb_height * framebuffer->fb_bpp), 
                     true);

    for (size_t y = 0; y < 256; y++) {
      for (size_t x = 0; x < 256; x++) {
        vga_drawpx(x + 200, y + 200, RGB(x, y, 0)); // Draw a gradient
      }
    }

    vga_draws("SurgeOS v1.3.1", 10, 10, RGB(255, 255, 255)); // Draw text
    vga_draws("Framebuffer initialized", 10, 20, RGB(0, 255, 0));
  } else {
    init_fallback_vga(); // Fallback to text mode
    vga_draws("Running in text mode", 0, 0, vga_entry_color(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK));
  }

  // Initialize virtual memory
  if (mmap) {
    vmem_init();
    serial_writes("Virtual Memory: Initialized\n");
    vga_virt_fb_addr(); // Map framebuffer to virtual memory
    vga_draws("Virtual Memory: Framebuffer mapped to virtual memory", 0, 30, RGB(0, 255, 0));
  } else {
    panic("No memory map found for virtual memory initialization");
  }

  

} 
