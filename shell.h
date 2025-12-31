#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

/* Function prototypes */
char *read_line(void);
char *trim_whitespace(char *str);
void execute(char *line);

extern char **environ;

#endif /* SHELL_H */
