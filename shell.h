#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/* prompt */
void print_prompt(void);

/* input */
char *read_input(void);
char *trim_spaces(char *str);

/* execution */
void execute_command(char *line);
int command_exists(char *path);
char *find_command(char *command);

#endif /* SHELL_H */

