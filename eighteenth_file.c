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

/**
 * removeEnvironmentVar - Removes an environment variable
 * @info: The structure holding potential arguments. Used for maintaining
 *        a constant function prototype.
 * @var: The string property of the environment variable
 * Return: 1 on delete, 0 otherwise
 */
int removeEnvironmentVar(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVar - Initializes a new environment variable
 *                     or modifies an existing one
 * @info: The structure holding potential arguments. Used for maintaining
 *        a constant function prototype.
 * @var: The string property of the environment variable
 * @value: The string value of the environment variable
 * Return: Always 0
 */
int setEnvironmentVar(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}
