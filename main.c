#include "shell.h"

/**
 * main - simple shell loop
 * Return: 0 on success
 */
int main(void)
{
    char *line;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("#cisfun$ ");

        line = read_line();
        if (!line)
        {
            printf("\n");
            break;
        }

        line = trim_whitespace(line);

        if (line[0] == '\0')
        {
            free(line);
            continue;
        }

        execute(line);

        free(line);
    }

    return 0;
}

