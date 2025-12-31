/*
 * File: main.c
 * Desc: Simple Shell main loop (0.1 → 0.3)
 */

#include "shell.h"
#include <unistd.h>

/**
 * main - entry point
 *
 * Return: exit status of last command
 */
int main(void)
{
	char *line = NULL;
	char *trimmed_line = NULL;
	int interactive = isatty(STDIN_FILENO);
	int last_status = 0;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_input();
		if (line == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		trimmed_line = trim_spaces_copy(line);
		free(line);
		line = NULL;

		if (trimmed_line == NULL || trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			continue;
		}

		last_status = execute_command(trimmed_line);
		free(trimmed_line);
		trimmed_line = NULL;
	}

	return (last_status);
}
