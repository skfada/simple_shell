#include "sajesh.h"

/**
 * sajesh_isChain - chain data
 * @buf: rteader
 * @p: pointer
 * @sk_data: data list
 * Return: integer 1
 */
int sajesh_isChain(sk_data_t *sk_data, char *buf, size_t *p)
{
	size_t count = *p;

	if (buf[count] == '|' && buf[count + 1] == '|')
	{
		buf[count] = 0;
		count++;
		sk_data->cmd_buf_type = CMD_OR;
	}
	else if (buf[count] == '&' && buf[count + 1] == '&')
	{
		buf[count] = 0;
		count++;
		sk_data->cmd_buf_type = CMD_AND;
	}
	else if (buf[count] == ';')
	{
		buf[count] = 0;
		sk_data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = count;
	return (1);
}

/**
 * sajesh_checkChain - checks the chain
 * @p: pointer
 * @i: index
 * @len: lenth
 * @sk_data: data linked
 * @buf: reader
 * Return: none
 */
void sajesh_checkChain(
sk_data_t *sk_data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t count = *p;

	if (sk_data->cmd_buf_type == CMD_AND)
	{
		if (sk_data->status)
		{
			buf[i] = 0;
			count = len;
		}
	}
	if (sk_data->cmd_buf_type == CMD_OR)
	{
		if (!sk_data->status)
		{
			buf[i] = 0;
			count = len;
		}
	}

	*p = count;
}

/**
 * sk_replaceAlias - change the alias
 * @sk_data: data link
 * Return: innter 1
 */
int sk_replaceAlias(sk_data_t *sk_data)
{
	char *ptr;
	list_t *node;
	int count;

	for (count = 0; count < 10; count++)
	{
		node = sajesh_nodeStartsWith
		(sk_data->alias, sk_data->argv[0], '=');
		if (!node)
			return (0);
		free(sk_data->argv[0]);
		ptr = sajesh_strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = sajesh__strdup(ptr + 1);
		if (!ptr)
			return (0);
		sk_data->argv[0] = ptr;
	}
	return (1);
}

/**
 * sajesh_replaceVars - rteplace variable
 * @sk_data: data link
 * Return: 0
 */
int sajesh_replaceVars(sk_data_t *sk_data)
{
	list_t *node;
	int count = 0;

	for (count = 0; sk_data->argv[count]; count++)
	{
		if (sk_data->argv[count][0] != '$' || !sk_data->argv[count][1])
			continue;

		if (!sajesh_strcmp(sk_data->argv[count], "$?"))
		{
			sk_replaceString(&(sk_data->argv[count]),
				sajesh__strdup(sajesh_convertNumber(sk_data->status, 10, 0)));
			continue;
		}
		if (!sajesh_strcmp(sk_data->argv[count], "$$"))
		{
			sk_replaceString(&(sk_data->argv[count]),
				sajesh__strdup(sajesh_convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = sajesh_nodeStartsWith(sk_data->env, &sk_data->argv[count][1], '=');
		if (node)
		{
			sk_replaceString(&(sk_data->argv[count]),
				sajesh__strdup(sajesh_strchr(node->str, '=') + 1));
			continue;
		}
		sk_replaceString(&sk_data->argv[count], sajesh__strdup(""));

	}
	return (0);
}

/**
 * sk_replaceString - replaceing the string
 * @old: imput the old string
 * @new: allow the bnew string
 *
 * Return: 1 rep replace 0 rep not replaces
 */
int sk_replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
