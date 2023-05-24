#include "sajesh.h"

/**
 * sajesh_strlen - the length of a string
 * Return: 1
 * @s: the string length to check.
 */
int sajesh_strlen(char *s)
{
	int count = 0;

	if (!s)
		return (0);

	while (*s++)
		count++;
	return (count);
}

/**
 * sajesh_strcmp - string to compare
 * Return: positive if s1 > s2, negative if s1 < s2,  zero if s1 == s2
 * @s2: the second strang
 * @s1: the first strang
 */
int sajesh_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * sajesh_startsWith - checks if needle starts with stack
 * Return: address of next char
 * @needle: the substring to find
 * @stack: string to search
 */
char *sajesh_startsWith(const char *stack, const char *needle)
{
	while (*needle)
		if (*needle++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * sajesh_strcat - concatenates two strings
 * Return: pointer to destination buffer
 * @src: the source buffer
 * @dest: the destination buffer*
 */
char *sajesh_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
