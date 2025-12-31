#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void)
{
	char *line;
	char *trimmed_line;

	while (1)
	{
	/* print prompt */
	printf(":) ");
	fflush(stdout);

	/* read input */
	line = read_input();
	if (!line)
	continue; /* user pressed Enter or EOF */

	/* trim spaces */
	trimmed_line = trim_spaces_copy(line);
	free(line); /* free the original line */

	if (!trimmed_line)
	continue; /* empty line */

	/* execute command */
	execute_command(trimmed_line);
	free(trimmed_line);
	}

	return 0;
}

