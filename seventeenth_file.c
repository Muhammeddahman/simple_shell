#include "shell.h"

/**
 * _printToStderr - Prints a string to stderr
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void _printToStderr(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putToStderr(str[i]);
		i++;
	}
}

/**
 * _putToStderr - Writes a character to stderr
 * @c:		The character to print
 *
 * Return:success 1. On error, -1 is returned, and errno is set appropriately.
 */
int _putToStderr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}


/**
 * _putToFD - Writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return:success 1. On error,-1 is returned, and errno is set appropriately.
 */
int _putToFD(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

