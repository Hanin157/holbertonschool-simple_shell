/*
 * File: shell.c
 * Desc: Input parsing, PATH handling and command execution
 */

#include "shell.h"

extern char **environ;

/**
 * is_space - checks for whitespace
 * @c: char
 *
 * Return: 1 if space-like, 0 otherwise
 */
int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * read_input - reads input line using getline
 *
 * Return: allocated string or NULL on EOF/error
 */
char *read_input(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t nread;

	nread = getline(&line, &size, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * trim_spaces_copy - remove leading & trailing spaces
 * @str: original string
 *
 * Return: new trimmed string or NULL if becomes empty
 */
char *trim_spaces_copy(char *str)
{
	char *end;
	char *trimmed;
	int len;

	if (!str)
		return (NULL);

	while (*str && is_space(*str))
		str++;

	if (*str == '\0')
		return (NULL);

	end = str + strlen(str) - 1;
	while (end > str && is_space(*end))
		end--;

	len = (int)(end - str) + 1;

	trimmed = malloc(len + 1);
	if (!trimmed)
		return (NULL);

	strncpy(trimmed, str, len);
	trimmed[len] = '\0';

	return (trimmed);
}

/**
 * command_exists - checks if path points to an executable file
 * @path: path to check
 *
 * Return: 1 if executable, 0 otherwise
 */
int command_exists(char *path)
{
	if (!path)
		return (0);

	if (access(path, X_OK) == 0)
		return (1);

	return (0);
}

/**
 * get_path_value - internal helper: get PATH from environ
 *
 * Return: pointer to PATH value (without "PATH=") or NULL
 */
static char *get_path_value(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * find_in_path - search command in PATH directories
 * @command: command name (no '/')
 *
 * Return: malloc'ed full path or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path, *path_copy, *dir;
	char *full_path;
	size_t len_dir, len_cmd;

	if (command == NULL)
		return (NULL);

	path = get_path_value();
	if (path == NULL || *path == '\0')
		return (NULL);

	path_copy = strdup(path);
	if (path_copy == NULL)
		return (NULL);

	len_cmd = strlen(command);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len_dir = strlen(dir);

		full_path = malloc(len_dir + 1 + len_cmd + 1);
		if (full_path == NULL)
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
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_command - returns either direct path or PATH-resolved path
 * @cmd: first argument (command name)
 *
 * Return: path to execute (may be same pointer as cmd) or NULL
 */
char *find_command(char *cmd)
{
	char *cmd_path;

	if (cmd == NULL)
		return (NULL);

	/* case 1: command contains '/' -> treat as a path */
	if (strchr(cmd, '/') != NULL)
	{
		if (command_exists(cmd))
			return (cmd); /* use as-is, do NOT free later */
		else
			return (NULL);
	}

	/* case 2: plain name -> search in PATH */
	cmd_path = find_in_path(cmd);
	return (cmd_path); /* malloc'ed if not NULL */
}

/**
 * execute_command - tokenizes & executes (with PATH + builtins)
 * @line: input line (trimmed)
 * @prog_name: program name (argv[0], e.g. "./hsh")
 * @cmd_count: current command number
 *
 * Return: exit status of command,
 *         127 if not found,
 *         -2 if builtin exit was called
 */
int execute_command(char *line, char *prog_name, int cmd_count)
{
	pid_t pid;
	int status = 0;
	char *args[128];
	char *token;
	int i = 0;
	char *cmd_path;
	int need_free = 0;

	if (!line || !line[0])
		return (0);

	/* split into arguments */
	token = strtok(line, " \t");
	while (token && i < 127)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	if (!args[0])
		return (0);

	/* built-in: exit (no arguments required for this task) */
	if (strcmp(args[0], "exit") == 0)
	{
		/* نرجع كود خاص، و main يتولى الخروج بعد ما يـfree */
		return (-2);
	}

	/* resolve command: either absolute/relative or via PATH */
	cmd_path = find_command(args[0]);
	if (cmd_path == NULL)
	{
		/* command doesn't exist → DO NOT fork */
		/* شكل الخطأ المطلوب: ./hsh: 1: ls: not found */
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_count, args[0]);
		return (127);
	}

	/* if find_command returned malloc'ed path (from PATH),
	 * it'll differ from args[0]
	 */
	if (cmd_path != args[0])
		need_free = 1;

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		if (need_free)
			free(cmd_path);
		return (1);
	}

	if (pid == 0)
	{
		/* child */
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(prog_name);
			if (need_free)
				free(cmd_path);
			_exit(127);
		}
	}
	else
	{
		/* parent */
		if (waitpid(pid, &status, 0) == -1)
		{
			perror(prog_name);
			status = 1;
		}
		else if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
		else
		{
			status = 1;
		}
	}

	if (need_free)
		free(cmd_path);

	return (status);
}
