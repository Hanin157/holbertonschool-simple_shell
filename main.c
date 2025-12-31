#include "shell.h"

int main(void)
{
    char *line;
    char *trimmed_line;

    while (1)
    {
        printf(":) ");
        fflush(stdout);

        line = read_input();
        if (!line)
            continue;

        trimmed_line = trim_spaces_copy(line);
        free(line);  /* safe now */

        if (!trimmed_line)
            continue;

        execute_command(trimmed_line);
        free(trimmed_line);
    }

    return 0;
}

