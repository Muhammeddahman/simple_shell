#include "shell.h"

/**
 * _customExit - exits the shell with a given exit status.
 * @info: Structure containing potential arguments.
 * Return: Exits with a specified exit status.
 *         (0) if info.argv[0] != "exit".
 */
int _customExit(info_t *info)
{
	int exitCode;

	if (info->argv[1])  /* Check for an exit argument */
	{
		exitCode = _erratoi(info->argv[1]);
		if (exitCode == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exitCode;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

