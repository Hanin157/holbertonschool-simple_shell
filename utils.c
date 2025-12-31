#include "shell.h"
#include <ctype.h>
#include <string.h>

/**
	* trim_whitespace - remove leading and trailing spaces/tabs in-place
	* @str: string to trim
	* Return: same pointer, trimmed in-place
	*/
char *trim_whitespace(char *str)
{
	char *end;

	if (!str)
	return NULL;

	while (isspace((unsigned char)*str))
	str++;

	if (*str == '\0')
	return str;

	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	end--;

	*(end + 1) = '\0';

	return str;
}

