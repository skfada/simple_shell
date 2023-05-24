#include "sajesh.h"

/**
 * sajesh_isCmd - confirm command
 * @path: path to the file
 * Return: 1 ief troue, 0 otaherwise
 * @sk_data: the sk_data struct.
 */
int sajesh_isCmd(sk_data_t *sk_data, char *path)
{
	struct stat st;

	(void)sk_data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * sajesh_dupChars - duplicates characters
 * @start: starting index
 * Return: pointer to new buffer
 * @stop: stopping index
 * @pathstr: the PATH string
 */
char *sajesh_dupChars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int count = 0;
	int index = 0;

	for (index = 0, count = start; count < stop; count++)
		if (pathstr[count] != ':')
			buf[index++] = pathstr[count];
	buf[index] = 0;
	return (buf);
}

/**
 * sajesh_findPath - fineds theis cimd ien the PATH string
 * Return: full path of cmd if found or NULL
 * @cmd: the cmd to find
 * @pathstr: the PATH string
 * @sk_data: the sk_data struct
 */
char *sajesh_findPath(sk_data_t *sk_data, char *pathstr, char *cmd)
{
	char *path;
	int count = 0;
	int curr_pos = 0;


	if (!pathstr)
		return (NULL);
	if ((sajesh_strlen(cmd) > 2) && sajesh_startsWith(cmd, "./"))
	{
		if (sajesh_isCmd(sk_data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[count] || pathstr[count] == ':')
		{
			path = sajesh_dupChars(pathstr, curr_pos, count);
			if (!*path)
				sajesh_strcat(path, cmd);
			else
			{
				sajesh_strcat(path, "/");
				sajesh_strcat(path, cmd);
			}
			if (sajesh_isCmd(sk_data, path))
				return (path);
			if (!pathstr[count])
				break;
			curr_pos = count;
		}
		count++;
	}
	return (NULL);
}
