#include "shell.h"

/**
 * insertNodeAtStart - Inserts a node at the beginning of the linked list
 * @head: Address of the pointer to the head node
 * @data: Data field of the node
 * @index: Index used for history
 *
 * Return: Pointer to the newly inserted node
 */
list_t *insertNodeAtStart(list_t **head, const char *data, int index)
{
	list_t *newNode;

	if (!head)
		return (NULL);

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->index = index;

	if (data)
	{
		newNode->data = _strdup(data);
		if (!newNode->data)
		{
			free(newNode);
			return (NULL);
		}
	}

	newNode->next = *head;
	*head = newNode;
	return (newNode);
}
