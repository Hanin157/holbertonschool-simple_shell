#include <unistd.h>    /* fork, execve, write */
#include <sys/wait.h>  /* waitpid */
#include <sys/stat.h>  /* stat */
#include <string.h>    /* strlen, strcpy, strcat, strtok */
#include <stdlib.h>    /* malloc, free, NULL */
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
	return (c == ' ' || c == '\t' || c == '\n');
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

	return line;
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
	* command_exists - checks if a command exists in the filesystem
	* @path: path to command
	*
	* Return: 1 if exists, 0 otherwise
	*/
int command_exists(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	return 1;
	return 0;
}

/**
	* find_command - finds the full path of a command using PATH variable
	* @command: command to search
	*
	* Return: full path string (must be freed) or NULL if not found
	*/
char *find_command(char *command)
{
	char *path_env = "/bin:/usr/bin:/usr/local/bin"; /* hardcoded PATH */
	char *path_copy, *dir;
	char *full_path;
	int len;

	if (command_exists(command))
	return strdup(command);

	path_copy = strdup(path_env);
	dir = strtok(path_copy, ":");

	while (dir)
	{
	len = strlen(dir) + strlen(command) + 2;
	full_path = malloc(len);
	if (!full_path)
	{
	free(path_copy);
	return NULL;
	}

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);

	if (command_exists(full_path))
	{
	free(path_copy);
	return full_path;
	}

	free(full_path);
	dir = strtok(NULL, ":");
	}

	free(path_copy);
	return NULL;
}

/**
	* execute_command - forks and executes a single command
	* @line: command line to execute
	*/
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[64]; /* support commands with arguments */
	char *token;
	int i = 0;
	char *full_path;

	/* tokenize command line */
	token = strtok(line, " ");
	while (token && i < 63)
	{
	args[i++] = token;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* find full path of command */
	full_path = find_command(args[0]);
	if (!full_path)
	{
	write(2, "./shell: command not found\n", 27);
	return;
	}

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	free(full_path);
	return;
	}

	if (pid == 0)
	{
	/* child process */
	if (execve(full_path, args, NULL) == -1)
	{
	perror("./shell");
	free(full_path);
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	/* parent waits for child */
	waitpid(pid, &status, 0);
	}

	free(full_path);
}

/**
	* print_prompt - prints the shell prompt
	*/
void print_prompt(void)
{
	write(1, "#cisfun$ ", 9);
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
	if (isatty(STDIN_FILENO))
	print_prompt();

	line = read_input();
	if (!line)
	break;

	trimmed_line = trim_spaces(line);
	free(line);
	if (!trimmed_line)
	continue;

	execute_command(trimmed_line);
	}

	return 0;
}

