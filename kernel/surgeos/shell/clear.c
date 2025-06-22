/**
 * SurgeOS shell clear.c
 * `clear` command implementation
 */

#include <surgeos/shell.h>
#include <drivers/tty.h>

int surgeos_shell_cmd_clear(int argc, char** argv) {
  // Clear the TTY screen
  tty_clear();
  
  // Print a new line to reset the prompt
  printf("\n: ");
  
  return 0; // Indicate success
}
