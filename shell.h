#ifndef SHELL_H
#define SHELL_H

char *read_input(void);
char *trim_spaces(char *str);
void execute_command(char *line);

#endif /* SHELL_H */

