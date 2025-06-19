/**
 * SurgeOS serial.h
 * Serial port driver
 */

#ifndef SURGEOS_SERIAL_H
#define SURGEOS_SERIAL_H

#include <stddef.h>
#include <stdint.h>

#define SERIAL_PORT 0x3F8 // COM1 port address

void serial_init(void);

// Checking functions
int serial_is_transmit_ready(void);

// Writing functions
void serial_writec(char c);
void serial_writes(const char* str);
void serial_write(const char* str, size_t len);
void serial_printf(const char* format, ...);

// Reading functions

#endif // SURGEOS_SERIAL_H
