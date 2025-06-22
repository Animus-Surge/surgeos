/**
 * SurgeOS shell.c
 * Shell function implementations
 */

#include <surgeos/shell.h>

#include <drivers/serial.h>

#include <stdio.h>
#include <string.h>

void surgeos_shell_init(void) {} //Nothing to do yet

void surgeos_shell_command(const char* cmd) {
  char cmd_copy[512];

  // Copy the command to a local buffer
  strncpy(cmd_copy, cmd, sizeof(cmd_copy) - 1);
  cmd_copy[sizeof(cmd_copy) - 1] = '\0'; // Ensure null-termination

  // Tokenize the command
  char** argv;

  size_t argc = 0;
  char* token = strtok(cmd_copy, " ");
  while (token != NULL && argc < 16) { // Limit to 16 arguments
    argv[argc++] = token;
    token = strtok(NULL, " ");
  }
  argv[argc] = NULL; // Null-terminate the argument list

  if (argc == 0) {
    return; // No command entered
  }

  for (size_t i = 0; i < command_count; i++) {
    if (strcmp(argv[0], commands[i].name) == 0) {
      // Found the command, execute it
      int result = commands[i].handler(argc, argv);
      if (result < 0) {
        serial_printf("Error executing command '%s': %d\n", commands[i].name, result);
      } else {
        serial_printf("Command '%s' executed successfully.\n", commands[i].name);
      }
      return;
    }
  }

  printf("SurgeOS: Command not found: %s\n", argv[0]);
  serial_printf("SurgeOS: Command not found: %s\n", argv[0]);
}
