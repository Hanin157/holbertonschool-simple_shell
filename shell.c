#include "shell.h"

/* checks if a character is space, tab, or newline */
int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/* read a line from stdin */
char *read_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
	free(line);
	return NULL;
	}

	if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	if (line[0] == '\0')
	{
	free(line);
	return NULL;
	}

	return line;
}

/* trim leading/trailing spaces and return a new allocated string */
char *trim_spaces_copy(char *str)
{
	char *end;
	char *trimmed;
	int len;

	if (!str)
	return NULL;

	while (is_space(*str))
	str++;

	if (*str == 0)
	return NULL;

	end = str + strlen(str) - 1;
	while (end > str && is_space(*end))
	end--;

	len = end - str + 1;
	trimmed = malloc(len + 1);
	if (!trimmed)
	return NULL;

	strncpy(trimmed, str, len);
	trimmed[len] = '\0';

	return trimmed;
}

/* check if command exists */
int command_exists(char *path)
{
	struct stat st;
	return (stat(path, &st) == 0);
}

/* find command in PATH */
char *find_command(char *command)
{
	char *path, *path_copy, *dir;
	char *full_path;
	int len;

	if (command_exists(command))
	return strdup(command);  /* always return new memory */

	path = getenv("PATH");
	if (!path)
	return NULL;

	path_copy = strdup(path);
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

/* execute command with arguments */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[128];
	int i = 0;
	char *token;
	char *line_copy;
	char *cmd_path;

	if (!line)
	return;

	line_copy = strdup(line); /* strtok_r modifies string */
	if (!line_copy)
	return;

	token = strtok(line_copy, " \t");
	while (token && i < 127)
	{
	args[i++] = token;
	token = strtok(NULL, " \t");
	}
	args[i] = NULL;

	/* check command exists */
	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
	fprintf(stderr, "./shell: command not found: %s\n", args[0]);
	free(line_copy);
	return;
	}

	pid = fork();
	if (pid == -1)
	{
	perror("fork");
	free(line_copy);
	free(cmd_path);
	return;
	}

	if (pid == 0)
	{
	if (execve(cmd_path, args, NULL) == -1)
	{
	perror("./shell");
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	waitpid(pid, &status, 0);
	}

	free(cmd_path);
	free(line_copy);
}

