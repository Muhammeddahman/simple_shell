#include "shell.h"

/**
 * main_loop - Main loop for the custom shell.
 * @shell_info: Pointer to the shell information struct.
 * @command_line_args: Argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int main_loop(shell_info_t *shell_info, char **command_line_args)
{
	ssize_t read_result = 0;
	int builtin_ret = 0;

	while (read_result != -1 && builtin_ret != -2)
	{
		clear_shell_info(shell_info);
		if (is_interactive(shell_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = get_input(shell_info);
		if (read_result != -1)
		{
			set_shell_info(shell_info, command_line_args);
			builtin_ret = find_builtin_command(shell_info);
			if (builtin_ret == -1)
				find_command(shell_info);
		}
		else if (is_interactive(shell_info))
			_putchar('\n');
		free_shell_info(shell_info, 0);
	}

	write_history(shell_info);
	free_shell_info(shell_info, 1);

	if (!is_interactive(shell_info) && shell_info->status)
		exit(shell_info->status);

	if (builtin_ret == -2)
	{
		if (shell_info->err_num == -1)
			exit(shell_info->status);
		exit(shell_info->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin_command - Finds a builtin command in the custom shell.
 * @shell_info: Pointer to the shell information struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit().
 */
int find_builtin_command(shell_info_t *shell_info)
{
	int i, builtin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(shell_info->argv[0], builtintbl[i].type) == 0)
		{
			shell_info->line_count++;
			builtin_ret = builtintbl[i].func(shell_info);
			break;
		}
	}

	return (builtin_ret);
}


/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			 || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
