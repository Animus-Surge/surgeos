/**
 * SurgeOS libk formatting.h
 * Formatting utilities header; used for printf-like functions
 */

#ifndef SURGEOS_FORMATTING_H
#define SURGEOS_FORMATTING_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

int fmt_hex(char* buf, uint32_t value, bool uppercase);
int fmt_int(char* buf, int value);
int fmt_uint(char* buf, unsigned int value);
int fmt_string(char* buf, const char* str);
int fmt_char(char* buf, char c);

// TODO: implement floating point and other formats

#endif // SURGEOS_FORMATTING_H
