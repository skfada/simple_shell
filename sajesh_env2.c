#include "sajesh.h"

/**
 * sajesh_getEnviron - the the environment
 * @sk_data: linked data
 * Return: 0
 */
char **sajesh_getEnviron(sk_data_t *sk_data)
{
	if (!sk_data->environ || sk_data->env_changed)
	{
		sk_data->environ = sajesh_listToStrings(sk_data->env);
		sk_data->env_changed = 0;
	}

	return (sk_data->environ);
}

/**
 * sajesh_unsetEnv - unset the env
 * Return: integet
 * @var: variable parameter
 * @sk_data: linked data paramete
 */
int sajesh_unsetEnv(sk_data_t *sk_data, char *var)
{
	size_t index = 0;
	char *ptr;
	list_t *node = sk_data->env;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = sajesh_startsWith(node->str, var);
		if (ptr && *ptr == '=')
		{
			sk_data->env_changed = sajesh_delNodeAtIindex(&(sk_data->env), index);
			index = 0;
			node = sk_data->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (sk_data->env_changed);
}

/**
 * sajesh_setEnv - set env
 * @var: variable parameter
 * @value: value parameter
 * Return: 0
 * @sk_data: linked list
 */
int sajesh_setEnv(sk_data_t *sk_data, char *var, char *value)
{
	list_t *node;
	char *ptr;
	char *buf = NULL;

	if (!var || !value)
		return (0);

	buf = malloc(sajesh_strlen(var) + sajesh_strlen(value) + 2);
	if (!buf)
		return (1);
	sajesh_strcpy(buf, var);
	sajesh_strcat(buf, "=");
	sajesh_strcat(buf, value);
	node = sk_data->env;
	while (node)
	{
		ptr = sajesh_startsWith(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			sk_data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	sajesh_addNode_end(&(sk_data->env), buf, 0);
	free(buf);
	sk_data->env_changed = 1;
	return (0);
}
