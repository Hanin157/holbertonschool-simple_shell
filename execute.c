#include "shell.h"

extern char **environ;

/**
	* execute_command - forks and executes a single-word command
	* @line: command to execute (full path)
	*/
void execute(char *line)
{
	pid_t child_pid;
	int status;
	char *args[2];

	if (line[0] == '\0') /* skip empty input */
		return;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}

	if (child_pid == 0) /* Child executes command */
	{
		args[0] = line;
		args[1] = NULL;

		if (execve(line, args, environ) == -1)
		{
			fprintf(stderr, "%s: No such file or directory\n", line);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent waits for child */
		waitpid(child_pid, &status, 0);
}

