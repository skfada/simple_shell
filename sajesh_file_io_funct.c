#include "sajesh.h"

/**
 * sajesh_getHistFile - get the list of history
 * Return: histort reatder
 * @sk_data: linked data parameter
 */

char *sajesh_getHistFile(sk_data_t *sk_data)
{
	char *dir;
	char *buf;

	dir = sajesh_getenv(sk_data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (sajesh_strlen(dir) +
			sajesh_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	sajesh_strcpy(buf, dir);
	sajesh_strcat(buf, "/");
	sajesh_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * sagesh_writeHist - write to the history
 * Return: 1
 * @sk_data: linked data parameter
 */
int sagesh_writeHist(sk_data_t *sk_data)
{
	list_t *node = NULL;
	char *filename = sajesh_getHistFile(sk_data);
	ssize_t fd;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = sk_data->history; node; node = node->next)
	{
		sajeshsajesh_putsfd(node->str, fd);
		sajesh_putfd('\n', fd);
	}
	sajesh_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * sajesh_readHist - read history from file
 * Return: history ccount
 * @sk_data: linked data parameter
 */
int sajesh_readHist(sk_data_t *sk_data)
{
	struct stat st;
	char *buf = NULL;
	int linecount = 0, last = 0, i;
	ssize_t rdlen, fd, fsize = 0;
	char *filename = sajesh_getHistFile(sk_data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			sajesh_buildHistList(sk_data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		sajesh_buildHistList(sk_data, buf + last, linecount++);
	free(buf);
	sk_data->histcount = linecount;
	while (sk_data->histcount-- >= HIST_MAX)
		sajesh_delNodeAtIindex(&(sk_data->history), 0);
	sajesh_renumberHist(sk_data);
	return (sk_data->histcount);
}

/**
 * sajesh_buildHistList - build history
 * @linecount: count line
 * Return: 0
 * @sk_data: linked data parameter
 * @buf: reader parameter
 */
int sajesh_buildHistList(sk_data_t *sk_data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (sk_data->history)
		node = sk_data->history;
	sajesh_addNode_end(&node, buf, linecount);

	if (!sk_data->history)
		sk_data->history = node;
	return (0);
}

/**
 * sajesh_renumberHist - renumber history list
 * Return: history count
 * @sk_data: liked data paramrter
 */
int sajesh_renumberHist(sk_data_t *sk_data)
{
	int index = 0;
	list_t *node = sk_data->history;

	while (node)
	{
		node->num = index++;
		node = node->next;
	}
	return (sk_data->histcount = index);
}
