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
