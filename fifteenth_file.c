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

/**
 * read_buffer - Reads a buffer
 * @info: Parameter struct
 * @buf: Buffer
 * @i: Size
 *
 * Return: Bytes read
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);
	bytes_read = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*i = bytes_read;
	return (bytes_read);
}

/**
 * custom_getline - Gets the next line of input from STDIN
 * @info: Parameter struct
 * @ptr: Address of pointer to buffer, preallocated or NULL
 * @length: Size of preallocated ptr buffer if not NULL
 *
 * Return: Bytes read
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_bytes = *length;
	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(info, buf, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, total_bytes, total_bytes ? total_bytes + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (total_bytes)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	total_bytes += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = total_bytes;
	*ptr = p;
	return (total_bytes);
}

/**
 * sigint_handler - Blocks ctrl-C
 * @sig_num: The signal number
 *
 * Return: Void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
