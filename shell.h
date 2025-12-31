#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>

extern char **environ;

/* main.c */
char *trim_whitespace(char *str);
char *read_line(void);
void execute_command(char *line);

#endif /* SHELL_H */

