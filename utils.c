#include "shell.h"

/**
	* trim_whitespace - removes leading and trailing spaces/tabs
	* @str: input string
	*
	* Return: new allocated trimmed string
	*/
char *trim_whitespace(char *str)
{
	char *end;

	if (str == NULL)
	return NULL;

	/* Trim leading spaces/tabs */
	while (*str == ' ' || *str == '\t')
	str++;

	if (*str == '\0') /* all spaces */
	return strdup("");

	/* Trim trailing spaces/tabs */
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
	end--;

	*(end + 1) = '\0';

	return strdup(str);
}

