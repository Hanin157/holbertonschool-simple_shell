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
		print_prompt();

		line = read_line();
		if (!line) /* Ctrl+D */
		{
			write(1, "\n", 1);
			break;
		}

		execute_command(line);
		free(line);
	}

	return (0);
}

