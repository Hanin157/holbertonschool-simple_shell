#include <unistd.h>    /* fork, execve */
#include <sys/wait.h>  /* waitpid */
#include <stdlib.h>    /* malloc, free, exit */
#include <stdio.h>     /* perror, printf */
#include <string.h>    /* strlen, strtok */
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
	* execute_command - forks and executes a command with optional arguments
	* @line: command line string
	*/
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[1024]; /* max 1024 arguments */
	char *token;
	int i = 0;

	/* Split line into command + arguments */
	token = strtok(line, " ");
	while (token != NULL && i < 1023)
	{
	args[i++] = token;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	return;
	}

	if (pid == 0)
	{
	if (execve(args[0], args, NULL) == -1)
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
	char *trimmed_line;

	while (1)
	{
	/* Print prompt only if input is from terminal */
	if (isatty(STDIN_FILENO))
	{
	write(1, "#cisfun$ ", 9);
	fflush(stdout);
	}

	line = read_input();
	if (line == NULL)
	break;

	trimmed_line = trim_spaces(line);
	if (trimmed_line == NULL)
	{
	free(line);
	continue;
	}

	execute_command(trimmed_line);
	free(line);
	}

	return (0);
}

