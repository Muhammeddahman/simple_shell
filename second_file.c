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


/**
 * memory_resize - Resizes a block of memory.
 *
 * @ptr: Pointer to the previous block.
 * @old_size: Original size of the block.
 * @new_size: New size of the block.
 * Return: A pointer to the resized block.
 */
void *memory_resize(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_block;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_block[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (new_block);
}
