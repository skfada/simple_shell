#include "sajesh.h"

/**
 * sajesh_strtow - splits a string into words.
 * Return: NULL on failure , a pointer to an array of strings
 * @d: the delimeter string
 * @str: the input string
 */
char **sajesh_strtow(char *str, char *d)
{
	char **str_ptr;
	int index, numwords = 0, jeg;
	int count, meg;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (index = 0; str[index] != '\0'; index++)
		if (!sajesh_isDelim(str[index], d) &&
			(sajesh_isDelim(str[index + 1], d) || !str[index + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	str_ptr = malloc((1 + numwords) * sizeof(char *));
	if (!str_ptr)
		return (NULL);
	for (index = 0, jeg = 0; jeg < numwords; jeg++)
	{
		while (sajesh_isDelim(str[index], d))
			index++;
		count = 0;
		while (!sajesh_isDelim(str[index + count], d) && str[index + count])
			count++;
		str_ptr[jeg] = malloc((count + 1) * sizeof(char));
		if (!str_ptr[jeg])
		{
			for (count = 0; count < jeg; count++)
				free(str_ptr[count]);
			free(str_ptr);
			return (NULL);
		}
		for (meg = 0; meg < count; meg++)
			str_ptr[jeg][meg] = str[index++];
		str_ptr[jeg][meg] = 0;
	}
	str_ptr[jeg] = NULL;
	return (str_ptr);
}

/**
 * **sajesh_strtow2 - splits a string into words
 * Return: a pointer to an array of strings,
 * @d: the delimeter
 * @str: the input string
 */
char **sajesh_strtow2(char *str, char d)
{
	int index, jeg, count;
	int mem, numwords = 0;
	char **str_ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (index = 0; str[index] != '\0'; index++)
		if ((str[index] != d && str[index + 1] == d) ||
		    (str[index] != d && !str[index + 1]) || str[index + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	str_ptr = malloc((1 + numwords) * sizeof(char *));
	if (!str_ptr)
		return (NULL);
	for (index = 0, jeg = 0; jeg < numwords; jeg++)
	{
		while (str[index] == d && str[index] != d)
			index++;
		count = 0;
		while (str[index + count] != d && str[index + count] && str[index +
			count] != d)
			count++;
		str_ptr[jeg] = malloc((count + 1) * sizeof(char));
		if (!str_ptr[jeg])
		{
			for (count = 0; count < jeg; count++)
				free(str_ptr[count]);
			free(str_ptr);
			return (NULL);
		}
		for (mem = 0; mem < count; mem++)
			str_ptr[jeg][mem] = str[index++];
		str_ptr[jeg][mem] = 0;
	}
	str_ptr[jeg] = NULL;
	return (str_ptr);
}
