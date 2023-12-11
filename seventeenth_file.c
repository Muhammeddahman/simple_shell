#include "shell.h"

/**
 * _printToStderr - Prints a string to stderr
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _printToStderr(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putToStderr(str[i]);
		i++;
	}
}
