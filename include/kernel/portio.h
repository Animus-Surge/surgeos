/**
 * SurgeOS kernel portio.h
 * inb, outb
 */

#ifndef SURGEOS_PORTIO_H
#define SURGEOS_PORTIO_H

#include <stdint.h>

// VGA port addresses
#define VGA_CRTC_INDEX      0x3D4 // CRTC Controller Index Register
#define VGA_CRTC_DATA       0x3D5 // CRTC Controller Data Register
#define VGA_GC_INDEX        0x3CE // Graphics Controller Index Register
#define VGA_GC_DATA         0x3CF // Graphics Controller Data Register
#define VGA_SEQUENCER_INDEX 0x3C4 // Sequencer Index Register
#define VGA_SEQUENCER_DATA  0x3C5 // Sequencer Data Register
#define VGA_AC_INDEX        0x3C0 // Attribute Controller Index Register
#define VGA_AC_DATA_WRITE   0x3C0 // Attribute Controller Data Write Register
#define VGA_AC_DATA_READ    0x3C1 // Attribute Controller Data Read Register
#define VGA_MISC_OUTPUT     0x3CC // Miscellaneous Output Read
#define VGA_MISC_OUTPUT_W   0x3C2 // Miscellaneous Output Write
#define VGA_INPUT_STATUS_1  0x3DA // Input Status Register 1 (VGA-specific)
#define VGA_DAC_INDEX       0x3C8 // Color index
#define VGA_DAC_DATA        0x3C9 // Color data
#define VGA_DAC_READ        0x3C7 // Color read

static inline void outb(uint16_t port, uint8_t value) {
  __asm__ volatile ("outb %0, %1" : : "a"(value), "dN"(port));
}

static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  __asm__ volatile ("inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

#endif
