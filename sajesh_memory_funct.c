#include "sajesh.h"

/**
 *sajesh_memset - fills memory with a constant byte
 *Return: (s) a pointer to the memory areas
 *@n: the amount of bytes to be filled
 *@b: the byte to fill *s with
 *@s: the pointer to the memory area
 */
char *sajesh_memset(char *s, char b, unsigned int n)
{
	unsigned int count;

	for (count = 0; count < n; count++)
		s[count] = b;
	return (s);
}

/**
 * sajesh_ffree - frees a string of strings
 * Return: void
 * @pp: string of strings
 */
void sajesh_ffree(char **pp)
{
	char **string = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(string);
}

/**
 * sajesh_realloc - reallocates a block of memory
 * Return: pointer to da ol'block nameen.
 * @newSize: byte size of new block
 * @oldSize: byte size of previous block
 * @ptr: pointer to previous malloc'ated block
 */
void *sajesh_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *previous;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	previous = malloc(newSize);
	if (!previous)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		previous[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (previous);
}
