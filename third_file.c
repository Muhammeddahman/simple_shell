#include "shell.h"

/**
 * my_free - Releases a pointer and sets its address to NULL.
 *
 * @pointer: The address of the pointer to be released.
 * Return: 1 if successfully freed, otherwise 0.
 */
int my_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
