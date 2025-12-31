#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

/* Prototypes */
char *read_line(void);
char *trim_whitespace(char *str);
void execute(char *line);

#endif

