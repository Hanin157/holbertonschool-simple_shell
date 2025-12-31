#include "shell.h"
#include <unistd.h>

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: exit status of last command
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *trimmed_line = NULL;
	int interactive = isatty(STDIN_FILENO);
	int last_status = 0;
	int cmd_count = 0;

	(void)argc;

	while (1)
	{
		if (interactive)
			print_prompt();

		line = read_input();
		if (line == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		trimmed_line = trim_spaces_copy(line);
		free(line);
		line = NULL;

		if (trimmed_line == NULL || trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			continue;
		}

		/* هذا الأمر رقم كم؟ */
		cmd_count++;

		/* نفّذ الأمر مع تمرير اسم البرنامج ورقم الأمر */
		last_status = execute_command(trimmed_line, argv[0], cmd_count);

		free(trimmed_line);
		trimmed_line = NULL;
	}

	return (last_status);
}

