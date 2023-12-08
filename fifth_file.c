#include "shell.h"

/**
 * custom_copy_string - Copies a source string to a destination buffer.
 *
 * @destination: The destination buffer.
 * @source: The source string to copy.
 * Return: Pointer to the destination buffer.
 */
char *custom_copy_string(char *destination, char *source)
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
