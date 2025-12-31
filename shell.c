#include "shell.h"
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
	* read_input - reads a line from stdin
	*
	* Return: pointer to the input line (must be freed by caller), or NULL on EOF
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
	* trim_spaces - removes leading and trailing spaces from a string
	* @str: input string
	*
	* Return: pointer to trimmed string (modifies original), or NULL if empty
	*/
char *trim_spaces(char *str)
{
	char *end;

	if (!str)
	return (NULL);

	while (isspace((unsigned char)*str))
	str++;

	if (*str == 0)
	return (NULL);

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	end--;

	*(end + 1) = '\0';
	return str;
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

