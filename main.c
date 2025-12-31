#include "shell.h"

/**
	* main - entry point for simple shell
	* @argc: argument count
	* @argv: argument vector
	*
	* Return: Always 0
	*/
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t child_pid;
	int status;

	(void)argc;
	(void)argv;

	while (1)
	{
	/* Display prompt */
	write(1, "#cisfun$ ", 9);

	/* Read user input */
	nread = getline(&line, &len, stdin);
	if (nread == -1) /* Ctrl+D or error */
	{
	write(1, "\n", 1);
	break;
	}

	/* Remove newline */
	if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	/* Skip empty input */
	if (line[0] == '\0')
	continue;

	/* Fork a child process */
	child_pid = fork();
	if (child_pid == -1)
	{
	perror("fork");
	continue;
	}

	if (child_pid == 0) /* Child executes command */
	{
	char *args[] = {line, NULL};
	if (execve(line, args, environ) == -1)
	{
	fprintf(stderr, "%s: No such file or directory\n", line);
	exit(EXIT_FAILURE);
	}
	}
	else /* Parent waits */
	waitpid(child_pid, &status, 0);
	}

	free(line);
	return (0);
}

