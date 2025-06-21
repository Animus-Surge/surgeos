/**
 * SurgeOS kernel keyboard.h
 * Keyboard driver header file
 */

#ifndef SURGEOS_KERNEL_KEYBOARD_H
#define SURGEOS_KERNEL_KEYBOARD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//TODO: support additional locales
typedef enum {
    SC_ESC        = 0x01,
    SC_1          = 0x02,
    SC_2          = 0x03,
    SC_3          = 0x04,
    SC_4          = 0x05,
    SC_5          = 0x06,
    SC_6          = 0x07,
    SC_7          = 0x08,
    SC_8          = 0x09,
    SC_9          = 0x0A,
    SC_0          = 0x0B,
    SC_MINUS      = 0x0C,
    SC_EQUALS     = 0x0D,
    SC_BACKSPACE  = 0x0E,
    SC_TAB        = 0x0F,
    SC_Q          = 0x10,
    SC_W          = 0x11,
    SC_E          = 0x12,
    SC_R          = 0x13,
    SC_T          = 0x14,
    SC_Y          = 0x15,
    SC_U          = 0x16,
    SC_I          = 0x17,
    SC_O          = 0x18,
    SC_P          = 0x19,
    SC_LBRACKET   = 0x1A,
    SC_RBRACKET   = 0x1B,
    SC_ENTER      = 0x1C,
    SC_LCTRL      = 0x1D,
    SC_A          = 0x1E,
    SC_S          = 0x1F,
    SC_D          = 0x20,
    SC_F          = 0x21,
    SC_G          = 0x22,
    SC_H          = 0x23,
    SC_J          = 0x24,
    SC_K          = 0x25,
    SC_L          = 0x26,
    SC_SEMICOLON  = 0x27,
    SC_APOSTROPHE = 0x28,
    SC_GRAVE      = 0x29,
    SC_LSHIFT     = 0x2A,
    SC_BACKSLASH  = 0x2B,
    SC_Z          = 0x2C,
    SC_X          = 0x2D,
    SC_C          = 0x2E,
    SC_V          = 0x2F,
    SC_B          = 0x30,
    SC_N          = 0x31,
    SC_M          = 0x32,
    SC_COMMA      = 0x33,
    SC_DOT        = 0x34,
    SC_SLASH      = 0x35,
    SC_RSHIFT     = 0x36,
    SC_KP_ASTERISK= 0x37,
    SC_LALT       = 0x38,
    SC_SPACE      = 0x39,
    SC_CAPSLOCK   = 0x3A,
} Scancode;

typedef enum {
  LC_EN_US,    // English (US)
  LC_EN_GB,    // English (UK)
               // TODO: add more
} locale_t;

typedef struct {
  // Keyboard state
  bool initialized;
  bool shift_pressed; // Shift key state
  bool ctrl_pressed;  // Control key state
  bool alt_pressed;   // Alt key state
  bool capslock_enabled; // Caps Lock state
  bool numlock_enabled; // Num Lock state
  bool scrolllock_enabled; // Scroll Lock state
  locale_t locale; // Current keyboard locale

  // Input buffer
  char buffer[256];
  size_t buffer_write_index;
  size_t buffer_read_index;
  size_t buffer_length;

  uint8_t key_state[16]; // 8*16 = 128 keys (0x00-0x7F)
  uint8_t key_state_ext[16]; // Extended keys (0x80-0xFF)

} keyboard_t;

// Helper functions
char sc_to_ascii(uint32_t);
char ascii_to_sc(char);

// Keyboard driver functions
void keyboard_init(void);

char keyboard_getchar(void);
void keyboard_addchar(char c);

#endif // SURGEOS_KERNEL_KEYBOARD_H
