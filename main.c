#include "shell.h"
#include <unistd.h> /* isatty */

/**
 * main - entry point for the simple shell
 *
 * Return: exit status of the last executed command
 */
int main(void)
{
	char *line = NULL;
	char *trimmed_line = NULL;
	int interactive;
	int last_status = 0;

	/* check if stdin is a terminal (interactive mode) */
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		/* show prompt only in interactive mode */
		if (interactive)
			print_prompt();

		/* read input */
		line = read_input();
		if (line == NULL)
		{
			/* EOF (Ctrl+D) or read error */
			if (interactive)
				printf("\n");
			break;
		}

		/* trim spaces (leading + trailing) */
		trimmed_line = trim_spaces_copy(line);
		free(line);
		line = NULL;

		/* empty line after trimming -> ignore */
		if (trimmed_line == NULL || trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			trimmed_line = NULL;
			continue;
		}

		/* execute command line (Task 2: one word, no PATH) */
		last_status = execute_command(trimmed_line);

		free(trimmed_line);
		trimmed_line = NULL;
	}

	return (last_status);
}

