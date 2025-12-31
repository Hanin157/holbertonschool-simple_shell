#include "shell.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Trim leading and trailing whitespace */
char *trim_whitespace(char *str)
{
    char *end;
    if (!str)
        return NULL;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == '\0')
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    *(end + 1) = '\0';
    return str;
}

