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

/**
 * _retrieveEnvVar - Gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: Environment variable name
 *
 * Return: The value of the environment variable
 */
char *_retrieveEnvVar(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

