/**
 * SurgeOS kernel keyboard.h
 * Keyboard driver header file
 */

#ifndef SURGEOS_KERNEL_KEYBOARD_H
#define SURGEOS_KERNEL_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

// TODO: move to <drivers>

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
} ExtendedScancode;

extern char buffer[256];
extern bool keyboard_enabled;

// Pressed key states
bool is_key_pressed(uint32_t scancode);
void set_key_pressed(uint32_t scancode, bool pressed);

// Scancode to ASCII conversion
char get_ascii_from_scancode(uint32_t scancode);
uint32_t get_scancode_from_ascii(char ascii);

#endif // SURGEOS_KERNEL_KEYBOARD_H
