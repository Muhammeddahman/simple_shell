#include "shell.h"

/**
 * buffer_input - Buffers chained commands
 * @info: Parameter struct
 * @buf: Address of buffer
 * @len: Address of length variable
 *
 * Return: Bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
#else
		bytes_read = custom_getline(info, buf, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buf)[bytes_read - 1] == '\n')
			{
				(*buf)[bytes_read - 1] = '\0'; /* Remove trailing newline */
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) Is this a command chain? */
			{
				*len = bytes_read;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_user_input - Gets a line minus the newline
 * @info: Parameter struct
 *
 * Return: Bytes read
 */
ssize_t get_user_input(info_t *info)
{
	static char *buf; /* The ';' command chain buffer */
	static size_t i, j, len;
	ssize_t bytes_read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytes_read = buffer_input(info, &buf, &len);
	if (bytes_read == -1) /* EOF */
		(return -1);
	if (len) /* We have commands left in the chain buffer */
	{
		j = i; /* Init new iterator to current buf position */
		p = buf + i; /* Get pointer for return */

		check_command_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_command_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';'' */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORMAL;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Else not a chain, pass back buffer from custom_getline() */
	return (bytes_read); /* Return length of buffer from custom_getline() */
}

