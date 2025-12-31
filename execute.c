#include "shell.h"

extern char **environ;

/* Execute a command given its full path */
void execute(char *line)
{
    pid_t child_pid;
    int status;
    char *args[2];

    if (line[0] == '\0')
        return;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return;
    }

    if (child_pid == 0) /* Child process */
    {
        args[0] = line;
        args[1] = NULL;

        if (execve(line, args, environ) == -1)
        {
            fprintf(stderr, "%s: No such file or directory\n", line);
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent waits */
        waitpid(child_pid, &status, 0);
}

