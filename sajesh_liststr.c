#include "sajesh.h"

/**
 * sajesh_addNode - add data to the beggining
 * @head: pointer to the head
 * @str: string of the node
 * @num: index of the node
 * Return: the list size
 */
list_t *sajesh_addNode(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	sajesh_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = sajesh__strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * sajesh_addNode_end - add data to the end of the linked list
 * @head: pointer address
 * @str: string of the linked list
 * @num: index of the node linked list
 * Return: list size
 */
list_t *sajesh_addNode_end(list_t **head, const char *str, int num)
{
	list_t *node;
	list_t *new_node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	sajesh_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = sajesh__strdup(str);
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

/**
 * sajesh_printListStr - prints string element
 * Return: list size
 * @h: history partameter
 * list_t: the linked list as parameter *
 */
size_t sajesh_printListStr(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		sajesh_puts(h->str ? h->str : "(nil)");
		sajesh_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * sajesh_delNodeAtIindex - removes node at given index
 * @head: pointer to the first node
 * @index: the index to delete
 * Return: 0 on failure 1 on success,
 */
int sajesh_delNodeAtIindex(list_t **head, unsigned int index)
{
	list_t *node;
	list_t *prev_node;
	unsigned int count = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		count++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * sajesh_freeList - free memmory in the list
 * Return: void
 * @head_ptr: pointer to the first link
 */
void sajesh_freeList(list_t **head_ptr)
{
	list_t *next_node;
	list_t *head;
	list_t *node;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
