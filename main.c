#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

/**
	* main - entry point for the simple shell
	*
	* Return: 0 on success
	*/
int main(void)
{
	char *line;
	char *trimmed_line;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	print_prompt();

	line = read_input();
	if (line == NULL)
	break;

	trimmed_line = trim_spaces(line);
	if (trimmed_line == NULL)
	{
	free(line);
	continue;
	}

	execute_command(trimmed_line);
	free(line);
	}

	return (0);
}

