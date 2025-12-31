#include "shell.h"

/**
	* main - simple shell loop
	* Return: 0 on success, 1 on failure
	*/
int main(void)
{
	char *line;

	while (1)
	{
	/* Display prompt */
	if (isatty(STDIN_FILENO))
	printf("#cisfun$ ");

	/* Read command line */
	line = read_line();
	if (!line) /* EOF (Ctrl+D) */
	{
	printf("\n");
	break;
	}

	/* Trim whitespace */
	line = trim_whitespace(line);

	/* Skip empty lines */
	if (line[0] == '\0')
	{
	free(line);
	continue;
	}

	/* Execute command */
	execute(line);

	free(line);
	}

	return (0);
}
