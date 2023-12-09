#include "shell.h"

/**
 * add_node - Adds a new node at the beginning of the linked list.
 * @head: Address of the pointer to the head node.
 * @data: Data field for the new node.
 * @index: Index used for history.
 *
 * Return: Pointer to the newly created node.
 */
list_t *add_node(list_t **head, const char *data, int index)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;

	if (data)
	{
		new_node->str = _strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

/**
 * add_node_end - Adds a new node at the end of the linked list.
 * @head: Address of the pointer to the head node.
 * @data: Data field for the new node.
 * @index: Index used for history.
 *
 * Return: Pointer to the newly created node.
 */
list_t *add_node_end(list_t **head, const char *data, int index)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;

	if (data)
	{
		new_node->str = _strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

