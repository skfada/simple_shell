#include "sajesh.h"

/**
 * main - entry point
 * @av: arg vector.
 * Return: 0 on success, 1 on error
 * @ac: arg count
 */
int main(int ac, char **av)
{
	int fd = 2;
	sk_data_t sk_data[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				sajesh_eputs(av[0]);
				sajesh_eputs(": 0: Can't open ");
				sajesh_eputs(av[1]);
				sajesh_eputchar('\n');
				sajesh_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		sk_data->readfd = fd;
	}
	sajesh_EnvList(sk_data);
	sajesh_readHist(sk_data);
	hsh(sk_data, av);
	return (EXIT_SUCCESS);
}
