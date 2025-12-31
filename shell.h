#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function declarations */
char *read_line(void);
char *trim_whitespace(char *str);
void execute_command(char *line);
void execute(char *line);

#endif /* SHELL_H */
