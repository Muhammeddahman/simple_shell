#include "shell.h"

/**
 * initializeInfo - Initializes the fields of an InfoStruct.
 * @info: The address of the InfoStruct.
 */
void initializeInfo(InfoStruct *info)
{
	info->argument = NULL;
	info->argumentsArray = NULL;
	info->executablePath = NULL;
	info->argumentCount = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

