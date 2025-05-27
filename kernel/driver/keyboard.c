/**
 * SurgeOS kernel driver/keyboard.c
 * Keyboard driver implementation
 */

#include <kernel/kernel.h>
#include <kernel/keyboard.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

// TODO: support additional layouts other than en_US

// scancode -> ASCII for unshifted keys (index = scancode)
const char scancode_to_ascii[128] = {
  0,    27,  '1', '2', '3', '4', '5', '6', '7', '8',   // 0x00-0x09
  '9',  '0',  '-', '=', 0,   '\t','q','w','e','r',     // 0x0A-0x13
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
  '(',  ')',  '_', '+', 0,   '\t','Q','W','E','R',     // 0x0A-0x13
  'T',  'Y',  'U', 'I', 'O', 'P', '{', '}', '\n',      // 0x14-0x1C
  0,    'A',  'S', 'D', 'F', 'G', 'H', 'J', 'K',       // 0x1D-0x25
  'L',  ':',  '"', '~', 0,   '|', 'Z', 'X', 'C', 'V',   // 0x26-0x2F
  'B',  'N',  'M', '<', '>', '?', 0,   '*', 0,         // 0x30-0x38
  ' ',  0,    0,    0,   0,   0,   0,   0,   0,         // 0x39-0x41
  0,    0,    0,    0,   0,   0,   0,   '7', '8', '9', // 0x42-0x4A (keypad)
  '-',  '4',  '5',  '6', '+', '1', '2', '3', '0', '.', // 0x4B-0x53 (keypad)
  0,    0,    0,    0,   0,   0,   0,   0,   0          // rest zero-filled
};

char get_ascii_from_scancode(uint32_t scancode) {
  static bool shift_pressed = false;
  static bool caps_lock = false;

  // Key release: bit 7 is set
  bool key_released = scancode & 0x80;
  uint8_t code = scancode & 0x7F;

  // === Update Modifier States ===
  switch (code) {
    case 0x2A: // Left Shift
    case 0x36: // Right Shift
      shift_pressed = !key_released;
      return 0;

    case 0x3A: // Caps Lock (toggle only on press)
      if (!key_released) {
        caps_lock = !caps_lock;
      }
      return 0;

    default:
      break;
  }

  // Ignore break codes (key releases)
  if (key_released) {
    return 0;
  }

  // Lookup base characters
  char ascii = shift_pressed ? scancode_to_ascii_shift[code]
    : scancode_to_ascii[code];

  // If it's a letter, apply Caps Lock XOR Shift logic
  if (isalpha(ascii)) {
    bool uppercase = shift_pressed ^ caps_lock;
    if (uppercase) {
      if (ascii >= 'a' && ascii <= 'z') {
        ascii -= 32;
      }
    } else {
      if (ascii >= 'A' && ascii <= 'Z') {
        ascii += 32;
      }
    }
  }

  return ascii;
}
