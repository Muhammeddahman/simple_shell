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

/**
 * displayError - Prints an error message
 * @info: The parameter & return info struct
 * @errorMessage: String containing specified error type
 * Return: No return value
 */
void displayError(info_t *info, char *errorMessage)
{
	_displayString(info->fileName);
	_displayString(": ");
	displayDecimal(info->lineCount, STDERR_FILENO);
	_displayString(": ");
	_displayString(info->arguments[0]);
	_displayString(": ");
	_displayString(errorMessage);
}

/**
 * displayDecimal - Prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 *
 * Return: Number of characters printed
 */
int displayDecimal(int input, int fd)
{
	int (*printChar)(char) = _putChar;
	int i, count = 0;
	unsigned int absoluteValue, current;

	if (fd == STDERR_FILENO)
		printChar = _eputChar;
	if (input < 0)
	{
		absoluteValue = -input;
		printChar('-');
		count++;
	}
	else
		absoluteValue = input;
	current = absoluteValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absoluteValue / i)
		{
			printChar('0' + current / i);
			count++;
		}
		current %= i;
	}
	printChar('0' + current);
	count++;

	return (count);
}

