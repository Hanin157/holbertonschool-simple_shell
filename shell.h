#ifndef SHELL_H
#define SHELL_H

/* main.c */
void print_prompt(void);
char *read_input(void);
char *trim_spaces(char *str);
void execute_command(char *line);

/* shell.c */
int is_space(char c);
int command_exists(char *path);
char *find_command(char *command);

#endif /* SHELL_H */

