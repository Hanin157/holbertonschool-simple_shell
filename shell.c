#include <unistd.h>    /* fork, execve */
#include <sys/wait.h>  /* waitpid */
#include <string.h>    /* strlen */
#include <stdlib.h>    /* malloc, free */
#include <stdio.h>     /* perror */
#include "shell.h"

/**
	* is_space - checks if a character is a space, tab, or newline
	* @c: character to check
	*
	* Return: 1 if space/tab/newline, 0 otherwise
	*/
int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
	return (1);
	return (0);
}

/**
	* read_input - reads a line from stdin
	*
	* Return: pointer to input line (must be freed), or NULL on EOF
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
	* trim_spaces - removes leading and trailing spaces/tabs/newlines
	* @str: input string
	*
	* Return: pointer to trimmed string, or NULL if empty
	*/
char *trim_spaces(char *str)
{
	char *end;

	if (!str)
	return (NULL);

	while (is_space(*str))
	str++;

	if (*str == 0)
	return (NULL);

	end = str + strlen(str) - 1;
	while (end > str && is_space(*end))
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
