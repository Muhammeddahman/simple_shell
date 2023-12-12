#include "shell.h"

/**
 * _shHistory - displays the history list, one command per line, preceded
 *              by line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _shHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

