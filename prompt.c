/*
 * File: prompt.c
 * Auth: Your Name
 * Desc: Functions related to the shell prompt.
 */

#include <unistd.h>
#include "shell.h"

/**
 * print_prompt - prints the shell prompt
 *
 * Return: void
 */
void print_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

