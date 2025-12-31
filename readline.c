#include "shell.h"

/**
	* read_line - read a line from stdin
	* Return: pointer to the line without newline (malloced)
	*/
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t n;

	n = getline(&line, &bufsize, stdin);
	if (n == -1)
	return NULL;

	if (n > 0 && line[n - 1] == '\n')
	line[n - 1] = '\0';

	return line;
}

