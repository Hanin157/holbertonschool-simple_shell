#include <stdlib.h>
#include <unistd.h>    /* isatty */
#include "shell.h"

int main(void)
{
	char *line;
	char *trimmed_line;

	while (1)
	{
	/* Print prompt only if input is from terminal */
	if (isatty(STDIN_FILENO))
	print_prompt();

	line = read_input();
	if (!line)
	break;

	trimmed_line = trim_spaces(line);
	free(line);
	if (!trimmed_line)
	continue;

	execute_command(trimmed_line);
	}

	return (0);
}

