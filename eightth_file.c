#include "shell.h"
int main()
{
	printf("Hello, world!\n");
	return (0);
}
/**
 * isInteractiveMode - Returns true if the shell is in interactive mode
 * @info: Pointer to the struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter
 * @c: The character to check
 * @delimiter: The delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 * isAlphabetic - Checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convertStringToInt - Converts a string to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int convertStringToInt(char *s)
{
	int i, sign = 1, flag = 0, result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		return (-result);
	else
		return (result);
}
