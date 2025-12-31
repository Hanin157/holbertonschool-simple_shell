#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/* prompt */
void print_prompt(void);

/* helpers */
int is_space(char c);
char *read_input(void);
char *trim_spaces_copy(char *str);

/* PATH helpers */
int command_exists(char *path);
char *find_in_path(char *command);

/* execution */
int execute_command(char *line);

#endif /* SHELL_H */
