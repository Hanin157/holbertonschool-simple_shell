#include <unistd.h> /* for write */
#include "shell.h"

/**
 * print_prompt - prints the shell prompt
 */
void print_prompt(void)
{
    write(1, "#cisfun$ ", 9);
}

