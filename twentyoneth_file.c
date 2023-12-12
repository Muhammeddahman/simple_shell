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

/**
 * remAlias - Removes an alias from the alias list.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @str: String parameter representing the alias to be removed.
 * Return: No return value
 */
int remAlias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}


/**
 * assAlias - Assigns an alias to a specified string.
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * @str: String parameter representing the alias to be assigned.
 * Return: No return value
 */

int assAlias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remAlias(info, str));

	remAlias(info, str);
	return (addNodeEnd(&(info->alias), str, 0) == NULL);
}


/**
 * disAlias - Displays the aliases.
 * @node: Node containing the alias information.
 * Return: No return value
 */
int disAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _shAlias - Placeholder function for an alias-related operation.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Placeholder return value
 */
int _shAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			disAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			assAlias(info, info->argv[i]);
		else
			disAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
