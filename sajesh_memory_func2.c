#include "sajesh.h"

/**
 * sajesh_bfree - free pointer
 * Return: 1 rep freed 0 rep otherwise.
 * @ptr: adreess of the head
 * Description: free pointer
 */
int sajesh_bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
