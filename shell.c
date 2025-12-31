#include "shell.h"
#include <sys/types.h>

extern char **environ;

/**
 * is_space - checks if a char is space, tab or newline
 * @c: character to check
 *
 * Return: 1 if space-like, 0 otherwise
 */
int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * read_input - reads a line from stdin using getline
 *
 * Return: allocated buffer (caller must free), or NULL on EOF/error
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

	/* strip trailing newline if present */
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * trim_spaces_copy - trims leading and trailing spaces in a new string
 * @str: original string
 *
 * Return: newly allocated trimmed string (caller must free), or NULL if empty
 */
char *trim_spaces_copy(char *str)
{
	char *end;
	char *trimmed;
	int len;

	if (str == NULL)
		return (NULL);

	/* skip leading spaces */
	while (*str && is_space(*str))
		str++;

	if (*str == '\0')
		return (NULL);

	/* move end pointer to last non-space char */
	end = str + strlen(str) - 1;
	while (end > str && is_space(*end))
		end--;

	len = (int)(end - str) + 1;

	trimmed = malloc(len + 1);
	if (trimmed == NULL)
		return (NULL);

	strncpy(trimmed, str, len);
	trimmed[len] = '\0';

	return (trimmed);
}

/**
 * execute_command - executes a single-word command (no PATH, no args)
 * @line: input line (already trimmed)
 *
 * Return: exit status of the command, or 1 on error
 */
int execute_command(char *line)
{
	pid_t pid;
	int status = 0;
	char *cmd;
	char *args[2];

	if (line == NULL || line[0] == '\0')
		return (0);

	/* Task 2: command lines are made only of one word
	 * we still tolerate extra spaces but ignore anything beyond first word
	 */
	cmd = strtok(line, " \t");
	if (cmd == NULL)
		return (0);

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("./hsh");
		return (1);
	}

	if (pid == 0)
	{
		/* child process: try to exec exactly what user typed */
		if (execve(cmd, args, environ) == -1)
		{
			/* same style as example: ./shell: No such file or directory */
			perror("./hsh");
			_exit(1);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("./hsh");
			return (1);
		}
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 1;
	}

	return (status);
}
