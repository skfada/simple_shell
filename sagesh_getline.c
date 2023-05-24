#include "sajesh.h"

/**
 * sajesh_inputBuf - user inpute strring
 * @sk_data: linked date
 * @buf: reader
 * @len: length
 *
 * Return: read byte
 */
ssize_t sajesh_inputBuf(sk_data_t *sk_data, char **buf, size_t *len)
{
	size_t len_p = 0;
	ssize_t r = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sagesh_sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = sajesh_getline(sk_data, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			sk_data->linecount_flag = 1;
			sajesh_removeComments(*buf);
			sajesh_buildHistList(sk_data, *buf, sk_data->histcount++);
			/* if (sajesh_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				sk_data->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - get input
 * @sk_data: data
 * Return: string len
 */
ssize_t get_input(sk_data_t *sk_data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(sk_data->arg), *p;

	sajesh_putchar(BUF_FLUSH);
	r = sajesh_inputBuf(sk_data, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		sajesh_checkChain(sk_data, buf, &j, i, len);
		while (j < len)
		{
			if (sajesh_isChain(sk_data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			sk_data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (sajesh_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * sajesh_readBuf - reads the buffer
 * @sk_data: data
 * @buf: reader
 * @i: index
 *
 * Return: value r
 */
ssize_t sajesh_readBuf(sk_data_t *sk_data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(sk_data->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * sajesh_getline - get the count of line
 * @sk_data: data of the line
 * @ptr: string value
 * @length: lenth of the value
 *
 * Return: value s
 */
int sajesh_getline(sk_data_t *sk_data, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = sajesh_readBuf(sk_data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = sajesh_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = sajesh_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		sajesh_strncat(new_p, buf + i, k - i);
	else
		sajesh_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sagesh_sigintHandler - handles signs
 * @sig_num: number
 *
 * Return: nothing
 */
void sagesh_sigintHandler(__attribute__((unused))int sig_num)
{
	sajesh_puts("\n");
	sajesh_puts("$ ");
	sajesh_putchar(BUF_FLUSH);
}
