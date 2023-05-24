#include "sajesh.h"

/**
 *sajesh_eputs - prints an input string
 * Return: none
 * @str: tring parameter
 */
void sajesh_eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		sajesh_eputchar(str[index]);
		index++;
	}
}

/**
 * sajesh_eputchar - print character
 * Return: 1
 * @c: character parameter
 */
int sajesh_eputchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int index;

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(2, buf, index);
		index = 0;
	}
	if (c != BUF_FLUSH)
		buf[index++] = c;
	return (1);
}

/**
 * sajesh_putfd - print funtion
 * @c: charecter parameter
 * Return: 1
 * @fd: file descriptor paraetr
 */
int sajesh_putfd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int count;

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(fd, buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buf[count++] = c;
	return (1);
}

/**
 *sajeshsajesh_putsfd - print file descriptor
 * @fd: file descriptor parameter
 * Return: index
 * @str: string parameter
 */
int sajeshsajesh_putsfd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += sajesh_putfd(*str++, fd);
	}
	return (index);
}
