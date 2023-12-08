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
