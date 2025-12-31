#include "shell.h"

/* Trim leading and trailing whitespace */
char *trim_whitespace(char *str)
{
    char *end;

    if (!str)
        return NULL;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
    return str;
}

/* Read a line from stdin dynamically */
char *read_line(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    nread = getline(&buffer, &bufsize, stdin);
    if (nread == -1)
        return NULL;

    if (buffer[nread - 1] == '\n')
        buffer[nread - 1] = '\0';

    return buffer;
}

