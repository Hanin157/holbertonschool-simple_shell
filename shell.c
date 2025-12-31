#include <unistd.h>    /* fork, execve */
#include <sys/wait.h>  /* waitpid */
#include <string.h>    /* strlen, strtok, strcpy, strcat */
#include <stdlib.h>    /* malloc, free, exit, getenv, strdup */
#include <stdio.h>     /* perror */
#include <sys/stat.h>  /* stat */
#include "shell.h"

/* Check if character is space, tab, or newline */
int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* Read a line from stdin */
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

/* Trim leading/trailing spaces */
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

/* Check if a command exists at path */
int command_exists(char *path)
{
	struct stat st;
	return (stat(path, &st) == 0);
}

/* Find full path of command using PATH */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char *full_path;
	int len;

	if (command_exists(command))
	return strdup(command);  /* Return a copy */

	path = getenv("PATH");
	if (!path)
	return (NULL);

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");

	while (dir)
	{
	len = strlen(dir) + strlen(command) + 2;
	full_path = malloc(len);
	if (!full_path)
	{
	free(path_copy);
	return (NULL);
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
	return (NULL);
}

/* Fork and execute a command with arguments */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[64];  /* Support multiple arguments */
	char *token;
	int i = 0;
	char *cmd_path;

	/* Split line into args */
	token = strtok(line, " ");
	while (token && i < 63)
	{
	args[i++] = token;
	token = strtok(NULL, " ");
	}
	args[i] = NULL;

	/* Find full path of command */
	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
	write(2, args[0], strlen(args[0]));
	write(2, ": command not found\n", 20);
	return;
	}

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	free(cmd_path);
	return;
	}

	if (pid == 0)  /* Child */
	{
	if (execve(cmd_path, args, NULL) == -1)
	{
	perror("execve");
	free(cmd_path);
	exit(EXIT_FAILURE);
	}
	}
	else  /* Parent */
	{
	waitpid(pid, &status, 0);
	free(cmd_path);
	}
}

