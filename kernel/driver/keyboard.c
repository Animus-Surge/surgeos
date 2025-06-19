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

uint8_t key_bitmap[16] = {0}; // Bitmap to track pressed keys

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

/**
 * @brief Returns if the key is currently pressed
 *
 * @param scancode The scancode to check
 * @return true if the key is pressed, false otherwise
 */
bool is_key_pressed(uint32_t scancode) {
  return (key_bitmap[scancode / 8] & (1 << (scancode % 8))) != 0;
}

/**
 * @brief Set the key state in the bitmap
 *
 * This function updates the key bitmap to reflect the current state of the key.
 *
 * @param scancode The scancode of the key
 * @param pressed True if the key is pressed, false if released
 */
void set_key_state(uint32_t scancode, bool pressed) {
  if (scancode & 0x80) { // Key release
    scancode &= 0x7F; // Clear the release bit
    if (pressed) {
      return; // Ignore setting a released key as pressed
    }
  } else { // Key press
    if (!pressed) {
      return; // Ignore setting a pressed key as released
    }
  }

  // Update the bitmap
  if (pressed) {
    key_bitmap[scancode / 8] |= (1 << (scancode % 8));
  } else {
    key_bitmap[scancode / 8] &= ~(1 << (scancode % 8));
  }
}

/**
 * @brief Convert a scancode to its ASCII representation
 *
 * This function takes a scancode as input and returns the corresponding ASCII character.
 *
 * It handles key presses, releases, and modifier keys like Shift and Caps Lock.
 *
 * @param scancode The scancode to convert
 * @return char The ASCII character corresponding to the scancode, or 0 if not applicable
 */
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

/**
 * @brief Convert an ASCII character to its scancode
 *
 * This function takes an ASCII character and returns the corresponding scancode.
 * It handles both uppercase and lowercase letters, as well as special characters.
 *
 * @param ascii The ASCII character to convert
 * @return uint32_t The corresponding scancode, or 0 if not found
 */
uint32_t get_scancode_from_ascii(char ascii) {
  // Handle uppercase letters
  if (isupper(ascii)) {
    ascii = tolower(ascii);
    return scancode_to_ascii_shift[ascii];
  }

  // Handle lowercase letters
  if (islower(ascii)) {
    return scancode_to_ascii[ascii];
  }

  // Handle special characters
  switch (ascii) {
    case '1': return scancode_to_ascii[0x02];
    case '2': return scancode_to_ascii[0x03];
    case '3': return scancode_to_ascii[0x04];
    case '4': return scancode_to_ascii[0x05];
    case '5': return scancode_to_ascii[0x06];
    case '6': return scancode_to_ascii[0x07];
    case '7': return scancode_to_ascii[0x08];
    case '8': return scancode_to_ascii[0x09];
    case '9': return scancode_to_ascii[0x0A];
    case '0': return scancode_to_ascii[0x0B];
    case '-': return scancode_to_ascii[0x0C];
    case '=': return scancode_to_ascii[0x0D];
    case '\b': return scancode_to_ascii[0x0E]; // Backspace
    case '\t': return scancode_to_ascii[0x0F]; // Tab
    case '[': return scancode_to_ascii[0x1A]; // Left bracket
    case ']': return scancode_to_ascii[0x1B]; // Right bracket
    case '\\': return scancode_to_ascii[0x2B]; // Backslash
    case ';': return scancode_to_ascii[0x27]; // Semicolon
    case '\'': return scancode_to_ascii[0x28]; // Apostrophe
    case ',': return scancode_to_ascii[0x33]; // Comma
    case '.': return scancode_to_ascii[0x34]; // Dot
    case '/': return scancode_to_ascii[0x35]; // Slash
    default: 
      if (ascii == ' ') {
        return scancode_to_ascii[0x39]; // Space
      }
      break;
  }

  // Not found, return 0
  return 0;
}
