/**
 * SurgeOS shell help.c
 * `help` command implementation
 */

#include <surgeos/shell.h>

#include <stdio.h>
#include <string.h>

int surgeos_shell_cmd_help(int argc, char** argv) {
  if (argc > 1) {
    printf("Usage: help\n");
    return -1;
  }

  printf("Available commands:\n");
  for (size_t i = 0; i < command_count; i++) {
    printf("  %s - %s\n", commands[i].name, commands[i].description);
  }
  
  return 0;
}
