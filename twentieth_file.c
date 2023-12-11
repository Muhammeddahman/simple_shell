#include "shell.h"

/**
 * isDelimiter-Tests if the current character in the buffer is chain delimiter
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int isDelimiter(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmdBufferType = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmdBufferType = CMD_AND;
	}
	else if (buf[j] == ';') /* Found end of this command */
	{
		buf[j] = 0; /* Replace semicolon with null */
		info->cmdBufferType = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - Checks if we should continue chaining based on the last status
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmdBufferType == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmdBufferType == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

