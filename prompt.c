/*
 * File: prompt.c
 * Desc: Handle prompt printing
 */

#include <unistd.h>
#include "shell.h"

/**
 * print_prompt - prints shell prompt when interactive
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
