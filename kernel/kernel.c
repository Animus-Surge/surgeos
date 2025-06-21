/**
 * SurgeOS kernel.c
 * Main kernel entry point
 */

#include <kernel/kernel.h>

#include <drivers/framebuffer.h>
#include <drivers/serial.h>
#include <drivers/tty.h>

#include <stdio.h>
#include <string.h>

void hsv_to_rgb_int(int hue, uint8_t *r, uint8_t *g, uint8_t *b) {
  uint8_t region = hue / 60;           // 0..5
  uint8_t remainder = (hue - (region * 60)) * 255 / 60;

  uint8_t p = 0;
  uint8_t q = 255 - ((remainder * 255) / 255);
  uint8_t t = (remainder * 255) / 255;

  // Since saturation=255 and value=255, p=0, q and t scale linearly

  switch(region) {
    case 0:
      *r = 255;
      *g = t;
      *b = 0;
      break;
    case 1:
      *r = q;
      *g = 255;
      *b = 0;
      break;
    case 2:
      *r = 0;
      *g = 255;
      *b = t;
      break;
    case 3:
      *r = 0;
      *g = q;
      *b = 255;
      break;
    case 4:
      *r = t;
      *g = 0;
      *b = 255;
      break;
    default:    // case 5:
      *r = 255;
      *g = 0;
      *b = q;
      break;
  }
}

void kernel_main() {
  tty_init();

  printf("\nSurgeOS v0.3.2\n\n\n");

  for (size_t x = 0; x < 360; x++) {
    uint8_t r, g, b;

    hsv_to_rgb_int(x, &r, &g, &b);
    uint32_t color = RGB(r, g, b);

    for (size_t y = 0; y < 8; y++) {
      framebuffer_drawpx(x + 8, y + 24, color);
    }
  }

  tty_loop();

  while (1) {} // Do nothing infinitely
}

