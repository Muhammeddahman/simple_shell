#include "shell.h"

/**
 * add_node - Adds a new node at the beginning of the linked list.
 * @head: Address of the pointer to the head node.
 * @data: Data field for the new node.
 * @index: Index used for history.
 *
 * Return: Pointer to the newly created node.
 */
list_t add_node(list_t **head, const char *data, int index)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;

	if (data)
	{
		new_node->str = strdup(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->my_next = *head;
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
list_t **add_node_end(list_t **head, const char *data, int index)
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
		while (node->my_next)
			node = node->my_next;
		node->my_next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - Prints only the str element of a list_t linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		puts(h->str ? h->str : "(nil)");
		puts("\n");
		h = h->my_next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - Deletes a node at the specified index.
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int *delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->my_next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->my_next = node->my_next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->my_next;
	}

	return (0);
}

/**
 * free_list - Frees all nodes of a linked list.
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->my_next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

