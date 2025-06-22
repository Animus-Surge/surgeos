/**
 * SurgeOS shell echo.c
 * `echo` command implementation
 */

#include <surgeos/shell.h>

#include <stdio.h>
#include <string.h>

int surgeos_shell_cmd_echo(int argc, char** argv) {
  if (argc < 2) {
    printf("Usage: echo <text>\n");
    return -1;
  }

  // Join the arguments into a single string
  char output[512] = {0};
  for (int i = 1; i < argc; i++) {
    if (i > 1) {
      strncat(output, " ", sizeof(output) - strlen(output) - 1);
    }
    strncat(output, argv[i], sizeof(output) - strlen(output) - 1);
  }

  printf("%s\n", output);
  return 0;
}
