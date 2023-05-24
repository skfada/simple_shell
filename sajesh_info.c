#include "sajesh.h"

/**
 * sagesh_clearSkData - clears the data struct
 * @sk_data: the linked list
 * Return: void
 */
void sagesh_clearSkData(sk_data_t *sk_data)
{
	sk_data->arg = NULL;
	sk_data->argv = NULL;
	sk_data->path = NULL;
	sk_data->argc = 0;
}

/**
 * sagesh_setSkData - clears the data
 * Return: void
 * @sk_data: linked data
 * @av: the argument vectos
 */
void sagesh_setSkData(sk_data_t *sk_data, char **av)
{
	int index = 0;

	sk_data->fname = av[0];
	if (sk_data->arg)
	{
		sk_data->argv = sajesh_strtow(sk_data->arg, " \t");
		if (!sk_data->argv)
		{

			sk_data->argv = malloc(sizeof(char *) * 2);
			if (sk_data->argv)
			{
				sk_data->argv[0] = sajesh__strdup(sk_data->arg);
				sk_data->argv[1] = NULL;
			}
		}
		for (index = 0; sk_data->argv && sk_data->argv[index]; index++)
			;
		sk_data->argc = index;

		sk_replaceAlias(sk_data);
		sajesh_replaceVars(sk_data);
	}
}

/**
 * sagesh_free_skData - free the data
 * @sk_data: linked data
 * Return: void
 * @all: freeing all data
 */
void sagesh_free_skData(sk_data_t *sk_data, int all)
{
	sajesh_ffree(sk_data->argv);
	sk_data->argv = NULL;
	sk_data->path = NULL;
	if (all)
	{
		if (!sk_data->cmd_buf)
			free(sk_data->arg);
		if (sk_data->env)
			sajesh_freeList(&(sk_data->env));
		if (sk_data->history)
			sajesh_freeList(&(sk_data->history));
		if (sk_data->alias)
			sajesh_freeList(&(sk_data->alias));
		sajesh_ffree(sk_data->environ);
			sk_data->environ = NULL;
		sajesh_bfree((void **)sk_data->cmd_buf);
		if (sk_data->readfd > 2)
			close(sk_data->readfd);
		sajesh_putchar(BUF_FLUSH);
	}
}
