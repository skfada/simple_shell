#include "sajesh.h"

/**
 * sajesh_strcpy - copies a string
 * Return: pointer to destination
 * @src: the source
 * @dest: the destination.
 */
char *sajesh_strcpy(char *dest, char *src)
{
	int count = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[count])
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = 0;
	return (dest);
}

/**
 * sajesh__strdup - duplicates a string
 * Return: pointer to the duplicated string
 * @str: the string to duplicate
 */
char *sajesh__strdup(const char *str)
{
	char *ret;
	int length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *sajesh_puts - prints an input string
 * Return: Nothing
 *@str: the string to be printed
 */
void sajesh_puts(char *str)
{
	int count = 0;

	if (!str)
		return;
	while (str[count] != '\0')
	{
		sajesh_putchar(str[count]);
		count++;
	}
}

/**
 * sajesh_putchar - writes the character c to stdout
 * Return: On success 1.
 * @c: The character to print
 */
int sajesh_putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int count;

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(1, buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buf[count++] = c;
	return (1);
}
