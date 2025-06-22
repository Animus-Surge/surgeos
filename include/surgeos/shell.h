/**
 * SurgeOS shell.h
 * SurgeOS shell header file
 */

#ifndef SURGEOS_SHELL_H
#define SURGEOS_SHELL_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// Command prototypes
int surgeos_shell_cmd_help(int, char**);
int surgeos_shell_cmd_echo(int, char**);
int surgeos_shell_cmd_clear(int, char**);
int surgeos_shell_cmd_exit(int, char**);
int surgeos_shell_cmd_reboot(int, char**);

typedef struct {
  const char* name;
  const char* description;
  int (*handler)(int argc, char** argv);
} command_t;
static const command_t commands[] = {
  {"help", "Display this help message", surgeos_shell_cmd_help},
  {"echo", "Echo the input text", surgeos_shell_cmd_echo},
  {"clear", "Clear the terminal screen", surgeos_shell_cmd_clear},
  {"exit", "Exit the shell", surgeos_shell_cmd_exit},
  {"reboot", "Reboot the system", surgeos_shell_cmd_reboot}
};
static const size_t command_count = 5;

// Shell utilities
void surgeos_shell_init(void);
void surgeos_shell_command(const char*);

#endif // SURGEOS_SHELL_H
