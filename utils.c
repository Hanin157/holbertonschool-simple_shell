#include "shell.h"

/**
	* trim_whitespace - remove leading and trailing spaces/tabs
	* @str: input string
	* Return: newly allocated string
	*/
char *trim_whitespace(char *str)
{
	char *end;

	if (!str)
	return NULL;

	while (*str == ' ' || *str == '\t')
	str++;

	if (*str == '\0')
	return strdup("");

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
	end--;

	*(end + 1) = '\0';
	return strdup(str);
}

