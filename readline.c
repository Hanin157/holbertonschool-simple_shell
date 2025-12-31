#include "shell.h"

/**
	* read_line - read a line from stdin
	* Return: allocated string (without newline)
	*/
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t n;

	n = getline(&line, &bufsize, stdin);
	if (n == -1)
	return NULL;

	/* Remove trailing newline if present */
	if (n > 0 && line[n - 1] == '\n')
	line[n - 1] = '\0';

	return line;
}

