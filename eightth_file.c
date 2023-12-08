#include "shell.h"

/**
 * isInteractiveMode - Returns true if the shell is in interactive mode
 * @info: Pointer to the struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * isDelimiter - Checks if a character is a delimiter
 * @c: The character to check
 * @delimiter: The delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

