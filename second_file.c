#include "shell.h"

/**
 * my_memset - Fills a memory region with a specific byte.
 *
 * @memory: Pointer to the memory area.
 * @value: The byte value to be set.
 * @size: The number of bytes to be set.
 * Return: A pointer to the memory area.
 */
char *my_memset(char *memory, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		memory[i] = value;

	return (memory);
}

/**
 * string_free - Deallocates a string array.
 *
 * @strings: The array of strings to be deallocated.
 */
void string_free(char **strings)
{
	char **temp = strings;

	if (!strings)
		return;

	while (*strings)
		free(*strings++);

	free(temp);
}
