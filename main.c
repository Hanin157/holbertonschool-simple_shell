/*
 * File: main.c
 * Desc: Simple Shell main loop (0.1 → 0.4)
 */

#include "shell.h"
#include <unistd.h>

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: exit status of last command
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *trimmed_line = NULL;
	int interactive = isatty(STDIN_FILENO);
	int last_status = 0;
	int cmd_count = 0;
	int status;

	(void)argc;

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
			trimmed_line = NULL;
			continue;
		}

		cmd_count++;

		status = execute_command(trimmed_line, argv[0], cmd_count);

		/* -2 معناها builtin exit */
		if (status == -2)
		{
			free(trimmed_line);
			trimmed_line = NULL;
			/* ممكن تخلي last_status كما هو أو 0، عادي غالباً */
			last_status = 0;
			break;
		}

		last_status = status;
		free(trimmed_line);
		trimmed_line = NULL;
	}

	return (last_status);
}
