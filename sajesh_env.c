#include "sajesh.h"

/**
 * sajesh_env - the env structur
 * @sk_data: link data
 * Return: 0
 */
int sajesh_env(sk_data_t *sk_data)
{
	sajesh_printListStr(sk_data->env);
	return (0);
}

/**
 * sajesh_getenv - function that get env
 * @sk_data: linked data
 * @name: the alias name
 * Return: null if failed
 */
char *sajesh_getenv(sk_data_t *sk_data, const char *name)
{
	char *ptr;
	list_t *node = sk_data->env;

	while (node)
	{
		ptr = sajesh_startsWith(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _sajeshSetEnv - get the saget env
 * @sk_data: linked data
 *  Return: 1
 */
int _sajeshSetEnv(sk_data_t *sk_data)
{
	if (sk_data->argc != 3)
	{
		sajesh_eputs("number of argument is incorrect\n");
		return (1);
	}
	if (sajesh_setEnv(sk_data, sk_data->argv[1], sk_data->argv[2]))
		return (0);
	return (1);
}

/**
 * _sajeshUnsetEnv - ynset the env
 * @sk_data: linked data
 *  Return: 0
 */
int _sajeshUnsetEnv(sk_data_t *sk_data)
{
	int index;

	if (sk_data->argc == 1)
	{
		sajesh_eputs("arguments entered are few.\n");
		return (1);
	}
	for (index = 1; index <= sk_data->argc; index++)
		sajesh_unsetEnv(sk_data, sk_data->argv[index]);

	return (0);
}

/**
 * sajesh_EnvList - list the environment
 * @sk_data: linked data
 * Return: 0
 */
int sajesh_EnvList(sk_data_t *sk_data)
{
	size_t index;
	list_t *node = NULL;

	for (index = 0; environ[index]; index++)
		sajesh_addNode_end(&node, environ[index], 0);
	sk_data->env = node;
	return (0);
}
