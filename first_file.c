#include "shell.h"

/**
 * custom_strlen - Calculate the length of a string.
 *
 * @s: The string whose length is to be determined.
 * Return: The length of the string.
 */
int custom_strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;

	return (length);
}


/**
 * custom_strcmp - Perform a lexicographic comparison of two strings.
 *
 * @s1: The first string.
 * @s2: The second string.
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2.
 */
int custom_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return ((*s1 < *s2) ? -1 : 1);
}
