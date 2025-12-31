#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/* prompt */
void print_prompt(void);

/* command execution */
int command_exists(char *path);
char *find_command(char *command);
void execute_command(char *line);

#endif

