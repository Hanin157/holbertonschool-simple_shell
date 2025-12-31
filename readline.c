#include "shell.h"

/**
	* read_line - reads a line from stdin
	*
	* Return: pointer to string (must free after use)
	*         NULL if EOF or error
	*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1) /* EOF (Ctrl+D) or error */
	{
		free(line);
		return (NULL);
	}

	/* Remove newline character */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

