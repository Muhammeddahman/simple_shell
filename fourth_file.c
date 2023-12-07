#include "shell.h"

/**
 * my_copy_string - Copies a string to a destination.
 *
 * @destination: The destination buffer.
 * @source: The source string to copy.
 * Return: Pointer to the destination buffer.
 */
char *my_copy_string(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
	return (destination);
}


/**
 * my_duplicate_string - Duplicates a given string.
 *
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string.
 */
char *my_duplicate_string(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	for (length++; length--;)
		result[length] = *--str;
	return (result);
}


/**
 * my_print_string - Prints a string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void my_print_string(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		my_putchar(str[index]);
		index++;
	}
}


/**
 * my_putchar - Writes a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buffer[index++] = c;
	return (1);
}

