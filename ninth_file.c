#include "shell.h"

/**
 * safeStringToInteger - Converts a string to an integer with error handling
 * @s: The string to be converted
 * Return: The converted number if successful, -1 on error
 */
int safeStringToInteger(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: Investigate the impact on main returning 255 */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

