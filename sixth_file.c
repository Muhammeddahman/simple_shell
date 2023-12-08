#include "shell.h"

/**
 * custom_split_string - Splits a string into substrings based on a delimiter
 * @str: The input string to be split
 * @delim: The delimiter used for splitting
 *
 * Return: An array of strings representing the substrings
 */
char **custom_split_string(char *str, char delim)
{
	int num_substrings = count_substrings(str, delim);
	char **substrings;

	if (num_substrings == 0)
		return (NULL);

	substrings = malloc((num_substrings + 1) * sizeof(char *));
	if (!substrings)
		return (NULL);

	split_and_store(substrings, str, delim);

	return (substrings);
}

