#include "shell.h"

/**
 * _printEnv - Displays the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _printEnv(info_t *info)
{
	printListStr(info->env);
	return (0);
}

