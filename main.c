#include "shell.h"

/**
	* main - entry point for simple shell v0.1
	*
	* Return: Always 0
	*/
int main(void)
{
	char *line;

	while (1)
	{
	/* Display prompt only in interactive mode */
	if (isatty(STDIN_FILENO))
	write(1, "#cisfun$ ", 9);

	line = read_line();
	if (!line) /* Ctrl+D */
	{
	if (isatty(STDIN_FILENO))
	write(1, "\n", 1);
	break;
	}

	execute_command(line);
	free(line);
	}

	return (0);
}
