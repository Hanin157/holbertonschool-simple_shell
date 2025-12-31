#include "shell.h"

/**
 * read_line - reads a line from stdin
 * Return: pointer to line (malloc), NULL on EOF/error
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        free(line);
        return NULL;
    }

    return line;
}

