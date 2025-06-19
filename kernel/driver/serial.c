/**
 * SurgeOS driver serial.c
 * Serial driver implementation
 */

#include <kernel/driver/serial.h>
#include <kernel/portio.h>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Initialize the serial port
 *
 * This function initializes the serial port by setting the baud rate,
 * line control, and enabling the FIFO.
 */
void serial_init(void) {
  outb(SERIAL_PORT + 1, 0x00); // Disable all interrupts
  outb(SERIAL_PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
  outb(SERIAL_PORT + 0, 0x01); // Set divisor to 1 (baud rate 115200)
  outb(SERIAL_PORT + 1, 0x00); // Disable DLAB
  outb(SERIAL_PORT + 3, 0x03); // 8 bits, no parity, one stop bit
  outb(SERIAL_PORT + 2, 0xC7); // Enable FIFO,clear them, with 14-byte threshold
  outb(SERIAL_PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

/**
 * @brief Check if the serial port is ready to transmit
 *
 * This function checks if the serial port is ready to transmit data.
 * It returns 1 if ready, 0 otherwise.
 *
 * @return int 1 if ready, 0 otherwise
 */
int serial_is_transmit_ready(void) {
  return (inb(SERIAL_PORT + 5) & 0x20); // Check if the transmit buffer is empt
}

/**
 * @brief Write a character to the serial port
 *
 * This function writes a single character to the serial port.
 *
 * @param c (char) the character to write
 */
void serial_writec(char c) {
  while (!serial_is_transmit_ready()); // Wait until ready
  outb(SERIAL_PORT, c); // Write the character
}

/**
 * @brief Write a string to the serial port
 *
 * This function writes a null-terminated string to the serial port.
 *
 * @param str (const char*) the string to write
 */
void serial_writes(const char* str) {
  while (*str) {
    if (*str == '\n') serial_writec('\r'); // Convert \n to \r\n
    serial_writec(*str++);
  }
}

/**
 * @brief Write a formatted string to the serial port
 *
 * This function writes a formatted string to the serial port using a format string.
 *
 * @param format (const char*) the format string
 * @param ... (variadic arguments) the values to format
 */
void serial_printf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  
  char buffer[256]; // Buffer for formatted output
  vsnprintf(buffer, sizeof(buffer), format, args); // Use vsnprintf to format the string
  
  serial_writes(buffer); // Write the formatted string to the serial port
  
  va_end(args);
}
