/*
 *
 * command.c
 *
 * This file implements running commands from the debug console.
 *
 */

#include "command.h"
#include "serial.h"
#include "stdint.h"
#include "string.h"


// Simulates the echo command
static void command_echo(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    serial_print(argv[i], SERIAL_TX);
    if (i != argc - 1) {
      serial_print(" ", SERIAL_TX);
    } else {
      serial_print("\n", SERIAL_TX);
    }
  }
}

// Replicates how main works on most computers to run commands
static void command_main(int argc, char **argv) {
  if (argc <= 0) return;
  if (strcmp("echo", argv[0]) == 0) {
    command_echo(argc, argv);
    return;
  }
}

// Executes the given command. Expects a c style string with terminating null byte.
void command_do(char *msg) {
  char *argv[MAX_ARGS];
  uint8_t argc = 1;
  argv[0] = msg;
  while (*msg != '\0' && argc < MAX_ARGS) {
    if (*msg == ' ') {
      // found end of argument
      *msg = '\0';
      msg++;
      argv[argc++] = msg;
    } else {
      msg++;
    }
  }
  command_main(argc, argv);
}
