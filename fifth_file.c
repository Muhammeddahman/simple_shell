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

/**
 * custom_duplicate_string - Duplicates a given string.
 *
 * @str: The string to duplicate.
 * Return: Pointer to the duplicated string.
 */
char *custom_duplicate_string(const char *str)
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
