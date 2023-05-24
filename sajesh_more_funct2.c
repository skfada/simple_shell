#include "sajesh.h"

/**
 * sajesh_erratoi - converts a string to an integer
 * Return: 1 for success 0 for fail
 * @s: the string to be converted.
 */
int sajesh_erratoi(char *s)
{
	unsigned long int result = 0;
	int count = 0;

	if (*s == '+')
		s++;
	for (count = 0;  s[count] != '\0'; count++)
	{
		if (s[count] >= '0' && s[count] <= '9')
		{
			result *= 10;
			result += (s[count] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * sajesh_printError - prints an error message
 * Return: void
 * @estr: string containing specified error type
 * @sk_data: the parameter & return sk_data struct
 */
void sajesh_printError(sk_data_t *sk_data, char *estr)
{
	sajesh_eputs(sk_data->fname);
	sajesh_eputs(": ");
	sajesh_print_d(sk_data->line_count, STDERR_FILENO);
	sajesh_eputs(": ");
	sajesh_eputs(sk_data->argv[0]);
	sajesh_eputs(": ");
	sajesh_eputs(estr);
}

/**
 * sajesh_print_d - print decimanl
 * Return: number of characters printed
 * @fd: the filedescriptor to write to
 * @input: user inpute
 */
int sajesh_print_d(int input, int fd)
{
	unsigned int _abs_, current;
	int count = 0;
	int index;
	int (*_sajesh_putchar)(char) = sajesh_putchar;

	if (fd == STDERR_FILENO)
		_sajesh_putchar = sajesh_eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		_sajesh_putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			_sajesh_putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	_sajesh_putchar('0' + current);
	count++;

	return (count);
}

/**
 * sajesh_convertNumber - number to character
 * @flags: argument flags
 * Return: string
 * @base: base parameter
 * @num: number paramete
 */
char *sajesh_convertNumber(long int num, int base, int flags)
{
	unsigned long n = num;
	char *ptr;
	char sign = 0;
	static char buffer[50];
	static char *array;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * sajesh_removeComments - removes the comment
 * Return: Always 0;
 * @buf: the reader
 */
void sajesh_removeComments(char *buf)
{
	int count;

	for (count = 0; buf[count] != '\0'; count++)
		if (buf[count] == '#' && (!count || buf[count - 1] == ' '))
		{
			buf[count] = '\0';
			break;
		}
}
