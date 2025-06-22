/**
 * SurgeOS driver tty.c
 * TTY driver implementation
 */

#include <drivers/framebuffer.h>
#include <drivers/keyboard.h>
#include <drivers/serial.h>
#include <drivers/tty.h>

#include <surgeos/shell.h>

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define TTY_COL_SIZE 8
#define TTY_ROW_SIZE 8

static tty_t tty = {0};

void tty_init(void) {
  // Initialize keyboard driver
  keyboard_init();

  // Get size of the framebuffer
  size_t fb_width = (size_t)framebuffer_get_width();
  size_t fb_height = (size_t)framebuffer_get_height();

  // Setup tty col and row sizes
  tty.width = fb_width / TTY_COL_SIZE;
  tty.height = fb_height / TTY_ROW_SIZE;

  tty.fg = RGB(128, 128, 128);
  tty.bg = RGB(0, 0, 0);

  // Clear screen
  framebuffer_clear();
  tty.new_line_ready = true;
}

void tty_loop() {
  // Main loop for TTY input handling
  //
  // TODO: handle control characters (C-c, C-d, etc.)
  while (true) {
    // State checking
    if(tty.new_line_ready) {
      tty.new_line_ready = false;
      printf("\n: ");

      tty.buf_pos = 0;
      tty.input_ready = true;
    }

    if (tty.cmd_ready) {
      tty.cmd_ready = false;
 
      char cmd[512];

      // Process the command
      for (size_t i = 0; i < tty.buf_pos; i++) {
        cmd[i] = tty.cmd_buffer[i];
      }
      cmd[tty.buf_pos] = '\0';
      serial_printf("TTY: Command: %s", cmd);

      surgeos_shell_command(cmd);

      // Post command
      tty.buf_pos = 0;
      tty.new_line_ready = true;
    }

    char c = keyboard_getchar();
    if (c && tty.input_ready) {
      // Check special characters
      if (c == '\n') {
        if (tty.buf_pos == 0) {
          // Just print a new command line
          tty.new_line_ready = true;
          tty.input_ready = false;
          continue;
        }
        tty.cmd_buffer[tty.buf_pos] = '\0';
        tty.input_ready = false;
        tty.cmd_ready = true;
      }
      else if (c == '\b') {
        if (tty.buf_pos > 0) {
          tty.buf_pos -= 1;
          printf("\b");
        }
        continue;
      }

      printf("%c", c);
      tty.cmd_buffer[tty.buf_pos] = c;
      tty.buf_pos++;
    }
  }
}

// Output functions

void tty_setchar(char c, size_t x, size_t y, uint32_t fg, uint32_t bg) {
  size_t fb_x = x * TTY_COL_SIZE;
  size_t fb_y = y * TTY_ROW_SIZE;

  framebuffer_drawc(c, fb_x, fb_y, fg, bg);
}

void tty_writechar(char c) {
  if (c == '\n') {
    tty.cursor_x = 0;

    if(++tty.cursor_y >= tty.height) {
      tty.cursor_y = 0;
    }
  } else if (c == '\b') {
    if (tty.cursor_x > 0) {
      tty.cursor_x--;
      tty_setchar(' ', tty.cursor_x, tty.cursor_y, tty.fg, tty.bg);
    }
    return; // Ignore backspace in this context
  } 

  tty_setchar(c, tty.cursor_x, tty.cursor_y, tty.fg, tty.bg);

  if(++tty.cursor_x >= tty.width) {
    tty.cursor_x = 0;
    
    if(++tty.cursor_y >= tty.height) {
      // TODO: implement scrolling
      tty.cursor_y = 0;
    }
  }
}

void tty_write(const char* str, size_t len) {
  for(size_t i = 0; i < len; i++) {
    tty_writechar(str[i]);
  }
}

void tty_clear() {
  framebuffer_clear();

  tty.cursor_x = 0;
  tty.cursor_y = 0;
}

// Color functions

// Cursor functions

