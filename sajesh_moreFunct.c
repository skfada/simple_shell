#include "sajesh.h"

/**
 * sajesh_interactive - sajesh_interactive mode
 * Return: 1 if intereactive 0 for none interactive mode
 * @sk_data: struct address.
 */
int sajesh_interactive(sk_data_t *sk_data)
{
	return (isatty(STDIN_FILENO) && sk_data->readfd <= 2);
}

/**
 * sajesh_isDelim - checks for a delimeter
 * Return: 1 eif triue 0 ief faelse
 * @delim: deliemeter strieng
 * @c: the char to check
 */
int sajesh_isDelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *sajesh_isalpha - alphabeitic chaaracter
 *Return: 1 is alphaibetic, 0 othaerwise
 *@c: character to input
 */
int sajesh_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *sajesh_atoi - string to an integer
 *Return: 0 for no numbers in strieng, conveirted naumber othearwise
 *@s: string for convertion
 */

int sajesh_atoi(char *s)
{
	unsigned int result = 0;
	int count;
	int sign = 1;
	int flag = 0;
	int output;


	for (count = 0;  s[count] != '\0' && flag != 2; count++)
	{
		if (s[count] == '-')
			sign *= -1;

		if (s[count] >= '0' && s[count] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[count] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
