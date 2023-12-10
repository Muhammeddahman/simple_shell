#include "fourteenth_file.h"

/**
 * main_loop - main loop for the custom shell
 * @shell_info: pointer to the shell information struct
 * @command_line_args: argument vector from main()
 *
 * Returns: 0 on success, 1 on error, or error code
 */
int main_loop(shell_info_t *shell_info, char **command_line_args)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_shell_info(shell_info);
		if (is_interactive(shell_info))
			display_prompt("$ ");
		flush_error_buffer();
		input_result = get_user_input(shell_info);
		if (input_result != -1)
		{
			configure_shell_info(shell_info, command_line_args);
			builtin_result = find_builtin_command(shell_info);
			if (builtin_result == -1)
				find_shell_command(shell_info);
		}
		else if (is_interactive(shell_info))
			display_newline();
		free_shell_info(shell_info, 0);
	}
	write_to_history(shell_info);
	free_shell_info(shell_info, 1);
	if (!is_interactive(shell_info) && shell_info->status)
		exit(shell_info->status);
	if (builtin_result == -2)
	{
		if (shell_info->error_number == -1)
			exit(shell_info->status);
		exit(shell_info->error_number);
	}
	return (builtin_result);
}
