/**
 * SurgeOS kernel driver/keyboard.c
 * Keyboard driver implementation
 */

#include <kernel/kernel.h>
#include <drivers/keyboard.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

// scancode -> ASCII for unshifted keys (index = scancode)
const char scancode_to_ascii[128] = {
  0,    27,  '1', '2', '3', '4', '5', '6', '7', '8',   // 0x00-0x09
  '9',  '0',  '-', '=', 8,   '\t','q','w','e','r',     // 0x0A-0x13
  't',  'y',  'u', 'i', 'o', 'p', '[', ']', '\n',      // 0x14-0x1C
  0,    'a',  's', 'd', 'f', 'g', 'h', 'j', 'k',       // 0x1D-0x25
  'l',  ';',  '\'', '`', 0,   '\\','z','x','c','v',     // 0x26-0x2F
  'b',  'n',  'm', ',', '.', '/', 0,   '*', 0,         // 0x30-0x38
  ' ',  0,    0,    0,   0,   0,   0,   0,   0,         // 0x39-0x41
  0,    0,    0,    0,   0,   0,   0,   '7', '8', '9', // 0x42-0x4A (keypad)
  '-',  '4',  '5',  '6', '+', '1', '2', '3', '0', '.', // 0x4B-0x53 (keypad)
  0,    0,    0,    0,   0,   0,   0,   0,   0          // rest zero-filled
};

// scancode -> ASCII for shifted keys (index = scancode)
const char scancode_to_ascii_shift[128] = {
  0,    27,  '!', '@', '#', '$', '%', '^', '&', '*',   // 0x00-0x09
  '(',  ')',  '_', '+', 8,   '\t','Q','W','E','R',     // 0x0A-0x13
  'T',  'Y',  'U', 'I', 'O', 'P', '{', '}', '\n',      // 0x14-0x1C
  0,    'A',  'S', 'D', 'F', 'G', 'H', 'J', 'K',       // 0x1D-0x25
  'L',  ':',  '"', '~', 0,   '|', 'Z', 'X', 'C', 'V',   // 0x26-0x2F
  'B',  'N',  'M', '<', '>', '?', 0,   '*', 0,         // 0x30-0x38
  ' ',  0,    0,    0,   0,   0,   0,   0,   0,         // 0x39-0x41
  0,    0,    0,    0,   0,   0,   0,   '7', '8', '9', // 0x42-0x4A (keypad)
  '-',  '4',  '5',  '6', '+', '1', '2', '3', '0', '.', // 0x4B-0x53 (keypad)
  0,    0,    0,    0,   0,   0,   0,   0,   0          // rest zero-filled
};

static keyboard_t keyboard = {0};

char sc_to_ascii(uint32_t scancode) {
  bool key_released = scancode & 0x80;
  uint8_t code = scancode & 0x7F;

  // Update modifier key state
  switch (code) {
    case 0x2A: // Left Shift
    case 0x36: // Right Shift
      keyboard.shift_pressed = !key_released;
      break;

    case 0x1D: // Ctrl
      keyboard.ctrl_pressed = !key_released;
      break;

    case 0x38: // Alt
      keyboard.alt_pressed = !key_released;
      break;

    case 0x3A: // Caps Lock
      if (!key_released) {
        keyboard.capslock_enabled = !keyboard.capslock_enabled;
      }
      break;

    // You could handle Num Lock / Scroll Lock here if needed
  }

  // Update key state bitmap (0x00-0x7F)
  uint8_t byte_index = code / 8;
  uint8_t bit_mask = 1 << (code % 8);
  if (key_released) {
    keyboard.key_state[byte_index] &= ~bit_mask;
    return 0;
  } else {
    keyboard.key_state[byte_index] |= bit_mask;
  }

  // Ignore key release scancodes
  if (key_released) return 0;

  // Lookup base character
  char ascii = keyboard.shift_pressed
    ? scancode_to_ascii_shift[code]
    : scancode_to_ascii[code];

  // Handle Caps Lock + Shift logic for letters
  if (isalpha(ascii)) {
    bool uppercase = keyboard.shift_pressed ^ keyboard.capslock_enabled;
    if (uppercase && ascii >= 'a' && ascii <= 'z') {
      ascii -= 32;
    } else if (!uppercase && ascii >= 'A' && ascii <= 'Z') {
      ascii += 32;
    }
  }

  return ascii;
}

/**
 * @brief Initialize the keyboard driver
 */
void keyboard_init(void) {
  // TODO: do something with control bytes too
  keyboard.initialized = true;
}

/**
 * @brief Get a character from the buffer
 *
 * This function retrieves a character from the keyboard buffer.
 *
 * @return The character read from the keyboard buffer, or 0 if not initialized or buffer is empty.
 */
char keyboard_getchar(void) {
  if (!keyboard.initialized) return 0;
  if (keyboard.buffer_length == 0) return 0;

  char c = keyboard.buffer[keyboard.buffer_read_index];
  keyboard.buffer_read_index++;
  keyboard.buffer_length--;

  if(keyboard.buffer_read_index >= 256) keyboard.buffer_read_index = 0;
  return c;
}

/**
 * @brief Add a character to the buffer
 *
 * This function adds a character to the keyboard buffer.
 *
 * @param c The character to add
 */
void keyboard_addchar(char c) {
  if (!keyboard.initialized) return; // Not initialized
  if (keyboard.buffer_length >= 256) return; // Buffer full

  keyboard.buffer[keyboard.buffer_write_index] = c;
  keyboard.buffer_write_index++;
  keyboard.buffer_length++;

  if (keyboard.buffer_write_index >= 256) keyboard.buffer_write_index = 0; // Wrap buffer index around
}
