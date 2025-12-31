#ifndef SHELL_H
#define SHELL_H

char *read_input(void);
char *trim_spaces(char *str);
void execute_command(char *line);

int is_space(char c);
int command_exists(char *path);
char *find_command(char *command);

#endif
