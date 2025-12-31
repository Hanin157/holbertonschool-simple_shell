#include "shell.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
	* trim_whitespace - removes leading and trailing whitespace
	* @str: string to trim
	*
	* Return: pointer to trimmed string
	*/
char *trim_whitespace(char *str)
{
	char *end;

	if (str == NULL)
	return (NULL);

	/* Trim leading space */
	while (*str && isspace((unsigned char)*str))
	str++;

	if (*str == '\0') /* All spaces */
	return strdup("");

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end))
	end--;

	*(end + 1) = '\0';

	return strdup(str);
}
