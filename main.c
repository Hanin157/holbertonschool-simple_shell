#include "shell.h"
#include <unistd.h>

/**
	* read_input - reads a line from stdin
	*
	* Return: pointer to the input line (must be freed by caller)
	*/
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
	free(line);
	return (NULL);
	}

	if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	if (line[0] == '\0')
	{
	free(line);
	return (NULL);
	}

	return (line);
}

/**
	* execute_command - forks and executes a single command
	* @line: command to execute
	*/
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	return;
	}

	if (pid == 0)
	{
	args[0] = line;
	args[1] = NULL;

	if (execve(line, args, NULL) == -1)
	{
	perror("./shell");
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	waitpid(pid, &status, 0);
	}
}

/**
	* main - entry point for the simple shell
	*
	* Return: 0 on success
	*/
int main(void)
{
	char *line;

	while (1)
	{
	/* Print prompt only if input is from terminal */
	if (isatty(STDIN_FILENO))
	{
	printf("#cisfun$ ");
	fflush(stdout);
	}

	line = read_input();
	if (line == NULL)
	break;

	execute_command(line);
	free(line);
	}

	return (0);
}

