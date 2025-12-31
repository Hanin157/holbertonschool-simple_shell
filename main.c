#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    pid_t pid;
    int status;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &bufsize, stdin);
        if (nread == -1)  /* Handle Ctrl+D */
        {
            printf("\n");
            break;
        }

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }

        if (pid == 0)  /* Child */
        {
            char *args[] = {line, NULL};

            if (execve(line, args, NULL) == -1)
            {
                perror("./shell");
                exit(EXIT_FAILURE);
            }
        }
        else  /* Parent */
        {
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}

