#include "shell.h"



/**
 * _customExit - Exits the shell with a given exit status.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a specified exit status (0 if info.argv[0] != "exit").
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



#include "shell.h"

/**
 * _customCd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int _customCd(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_result;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_result = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_result = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
			return (_puts(current_dir), _putchar('\n'), 1);

		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);

	if (chdir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

