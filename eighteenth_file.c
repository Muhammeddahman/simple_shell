#include "shell.h"

/**
 * fetchEnvironment - Retrieves the string array copy of our environment
 * @info: The structure holding potential arguments. Used for maintaining
 *        a constant function prototype.
 * Return: Always 0
 */
char **fetchEnvironment(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = listToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environ);
}

