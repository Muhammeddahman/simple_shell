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

