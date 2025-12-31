#include "shell.h"

/**
 * trim_whitespace - removes leading/trailing spaces
 * @str: string to trim
 * Return: new string (malloc)
 */
char *trim_whitespace(char *str)
{
    char *end;

    if (!str)
        return NULL;

    while (*str && isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return strdup("");

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';

    return strdup(str);
}

