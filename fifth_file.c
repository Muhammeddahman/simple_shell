#include "shell.h"

/**
 * custom_copy_n_string - Copies a source string
 *			to a destination buffer with a limit.
 *
 * @destination: The destination buffer.
 * @source: The source string to copy.
 * @n: The maximum number of characters to copy.
 * Return: Pointer to the destination buffer.
 */
char *custom_copy_n_string(char *destination, char *source, int n)
{
	int index, j;
	char *result = destination;

	index = 0;
	while (source[index] != '\0' && index < n - 1)
	{
		destination[index] = source[index];
		index++;
	}
	if (index < n)
	{
		j = index;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

