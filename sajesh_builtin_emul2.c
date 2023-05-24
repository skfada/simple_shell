#include "sajesh.h"
/**
 * sajesh_hist - history data
 * @sk_data: linked data
 * Return: 0 interger
 */
int sajesh_hist(sk_data_t *sk_data)
{
	sajesh_printList(sk_data->history);
	return (0);
}

/**
 * sk_unsetAlias - unset the alias environment
 * @sk_data: lin ked list
 * @str: string
 * Return: inter 1 or 0
 */
int sk_unsetAlias(sk_data_t *sk_data, char *str)
{
	int ret;
	char *p, c;

	p = sajesh_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = sajesh_delNodeAtIindex(&(sk_data->alias),
		sajesh_getNodeIndex
		(sk_data->alias, sajesh_nodeStartsWith(sk_data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * sk_setAlias - set alias
 * @sk_data: linked data
 * @str: string
 * Return: 1 or 0
 */
int sk_setAlias(sk_data_t *sk_data, char *str)
{
	char *ptr;

	ptr = sajesh_strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (sk_unsetAlias(sk_data, str));

	sk_unsetAlias(sk_data, str);
	return (sajesh_addNode_end(&(sk_data->alias), str, 0) == NULL);
}

/**
 * sk_printAlias - print the alias
 * @node: the linked list
 * Return: integer
 */
int sk_printAlias(list_t *node)
{
	char *ptr = NULL, *alias = NULL;

	if (node)
	{
		ptr = sajesh_strchr(node->str, '=');
		for (alias = node->str; alias <= ptr; alias++)
			sajesh_putchar(*alias);
		sajesh_putchar('\'');
		sajesh_puts(ptr + 1);
		sajesh_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * sajesh_alias - alias
 * @sk_data: data
 * Return: integer
 */
int sajesh_alias(sk_data_t *sk_data)
{
	list_t *node = NULL;
	char *ptr = NULL;
	int index = 0;

	if (sk_data->argc == 1)
	{
		node = sk_data->alias;
		while (node)
		{
			sk_printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (index = 1; sk_data->argv[index]; index++)
	{
		ptr = sajesh_strchr(sk_data->argv[index], '=');
		if (ptr)
			sk_setAlias(sk_data, sk_data->argv[index]);
		else
			sk_printAlias(sajesh_nodeStartsWith(sk_data->alias,
			sk_data->argv[index], '='));
	}

	return (0);
}
