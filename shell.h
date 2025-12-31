#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/* helper functions */
int is_space(char c);
char *read_input(void);
char *trim_spaces_copy(char *str);
void execute_command(char *line);

/* PATH handling */
int command_exists(char *path);
char *find_command(char *command);

#endif

