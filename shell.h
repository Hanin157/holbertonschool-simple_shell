#ifndef SHELL_H
#define SHELL_H

/* Function prototypes */
char *read_input(void);
char *trim_spaces(char *str);
void execute_command(char *line);
void print_prompt(void);

#endif /* SHELL_H */

