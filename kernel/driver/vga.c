/**
 * SurgeOS kernel driver/vga.c
 * Graphics mode vga driver implementation
 */

#include <stdint.h>
#include <stddef.h>

#include <kernel/vga.h>

#include <kernel/portio.h>

static uint8_t vga_mode;
static uint16_t flags = 0;
static size_t vga_width, vga_height;
static volatile uint16_t* vga_textmode_buffer = (volatile uint16_t*)VGA_TEXT_MODE_ADDRESS;
static volatile uint8_t* vga_rastermode_buffer = (volatile uint8_t*)VGA_RASTER_MODE_ADDRESS;

int vga_init(uint8_t mode) {
}

void vga_clear(void) {
}

void vga_put(size_t row, size_t col, uint16_t entry) {
}

void vga_set_dac_entry(rgbcolor_t color, uint8_t index) {
}

void vga_load_palette(rgbcolor_t* palette, size_t len) {
}

void vga_putpixel(size_t x, size_t y, uint8_t color) {
}

