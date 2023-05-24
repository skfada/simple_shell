#include "sajesh.h"

/**
 *sajesh_strncpy - copies a string
 *Return: the concatenated string
 *@dest: the destination string to be copied to.
 *@n: the amount of characters to be copied.
 *@src: the source string.
 */
char *sajesh_strncpy(char *dest, char *src, int n)
{
	char *s = dest;
	int index;
	int count;

	index = 0;
	while (src[index] != '\0' && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}
	if (index < n)
	{
		count = index;
		while (count < n)
		{
			dest[count] = '\0';
			count++;
		}
	}
	return (s);
}

/**
 *sajesh_strncat - concatenates two strings
 *Return: the concatenated string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *@dest: the first string
 */
char *sajesh_strncat(char *dest, char *src, int n)
{
	char *s = dest;
	int index;
	int count;


	index = 0;
	count = 0;
	while (dest[index] != '\0')
		index++;
	while (src[count] != '\0' && count < n)
	{
		dest[index] = src[count];
		index++;
		count++;
	}
	if (count < n)
		dest[index] = '\0';
	return (s);
}

/**
 *sajesh_strchr - locates a character in a string
 *Return: a pointer to the memory area
 *@c: the character to look for
 *@s: the string to be parsed
 */
char *sajesh_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
