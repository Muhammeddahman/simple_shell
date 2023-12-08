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

/**
 * custom_concatenate_n_strings - Concatenates two strings
 *			with a limit on the number of characters.
 *
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used.
 * Return: The concatenated string.
 */
char *custom_concatenate_n_strings(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (result);
}

/**
 * custom_find_character - Locates a character in a string.
 *
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of the character in the string
 *				, or NULL if not found.
 */
char *custom_find_character(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
