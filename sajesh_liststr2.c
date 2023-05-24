#include "sajesh.h"

/**
 * sajesh_listLen - defines the lenth of the link
 * Return: linked list size
 * @h: pointer to the first head
 */
size_t sajesh_listLen(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * sajesh_listToStrings - the list of strings
 * Return: string arrays
 * @head: pointer to first node
 */
char **sajesh_listToStrings(list_t *head)
{
	char **strs;
	list_t *node = head;
	char *str;
	size_t index = sajesh_listLen(head);
	size_t count;


	if (!head || !index)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));
	if (!strs)
		return (NULL);
	for (index = 0; node; node = node->next, index++)
	{
		str = malloc(sajesh_strlen(node->str) + 1);
		if (!str)
		{
			for (count = 0; count < index; count++)
				free(strs[count]);
			free(strs);
			return (NULL);
		}

		str = sajesh_strcpy(str, node->str);
		strs[index] = str;
	}
	strs[index] = NULL;
	return (strs);
}

/**
 * sajesh_printList - print the linked list
 * @h: points to the first linked list
 * Return: linked list size
 */
size_t sajesh_printList(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		sajesh_puts(sajesh_convertNumber(h->num, 10, 0));
		sajesh_putchar(':');
		sajesh_putchar(' ');
		sajesh_puts(h->str ? h->str : "(nil)");
		sajesh_puts("\n");
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * sajesh_nodeStartsWith - nodes with prefix
 * @c: the chatracter parameter
 * Return: null or math prefix
 * @node: the linked list
 * @prefix: to match the strioct prefix
 */
list_t *sajesh_nodeStartsWith(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = sajesh_startsWith(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * sajesh_getNodeIndex - the node index
 * Return: index of node or -1
 * @node: linked list data
 * @head: the head pointer
 */
ssize_t sajesh_getNodeIndex(list_t *head, list_t *node)
{
	size_t count = 0;

	while (head)
	{
		if (head == node)
			return (count);
		head = head->next;
		count++;
	}
	return (-1);
}
