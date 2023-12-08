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

/**
 * count_substrings - Counts the number of substrings in a string
 * @str: The input string
 * @delim: The delimiter used for counting
 *
 * Return: The number of substrings
 */
int count_substrings(char *str, char delim)
{
	int count = 0;
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == delim)
		{
			count++;
			while (str[i + 1] == delim)
				i++; /* Skip consecutive delimiters */
		}
	}

	return (count + 1); /* Add 1 for the last substring */
}

/**
 * split_and_store - Splits a string and stores substrings in an array
 * @substrings: The array to store the substrings
 * @str: The input string to be split
 * @delim: The delimiter used for splitting
 */
void split_and_store(char **substrings, char *str, char delim)
{
	int i, j, k;

	for (i = 0, j = 0; str[i] != '\0'; i++)
	{
		while (str[i] == delim)
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] != '\0')
			k++;

		substrings[j] = substring_copy(str + i, k);
		if (!substrings[j])
		{
			free_substrings(substrings, j);
			return;
		}

		i += k;
		j++;
	}

	substrings[j] = NULL;
}

/**
 * substring_copy - Copies a substring from a string
 * @start: The starting point of the substring
 * @length: The length of the substring
 *
 * Return: A newly allocated string containing the substring
 */
char *substring_copy(char *start, int length)
{
	char *substring = malloc((length + 1) * sizeof(char));

	if (!substring)
		return (NULL);

	for (int i = 0; i < length; i++)
		substring[i] = start[i];

	substring[length] = '\0';
	return (substring);
}

