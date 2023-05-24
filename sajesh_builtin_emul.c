#include "sajesh.h"

/**
 * sajesh_exit - exit command
 * @sk_data: data link
 * Return: status
 */
int sajesh_exit(sk_data_t *sk_data)
{
	int exitcheck;

	if (sk_data->argv[1])
	{
		exitcheck = sajesh_erratoi(sk_data->argv[1]);
		if (exitcheck == -1)
		{
			sk_data->status = 2;
			sajesh_printError(sk_data, "just dey play: ");
			sajesh_eputs(sk_data->argv[1]);
			sajesh_eputchar('\n');
			return (1);
		}
		sk_data->err_num = sajesh_erratoi(sk_data->argv[1]);
		return (-2);
	}
	sk_data->err_num = -1;
	return (-2);
}

/**
 * sajesh_cd - change directory
 * @sk_data: data linkl
 *  Return: 0
 */
int sajesh_cd(sk_data_t *sk_data)
{
	int chdir_ret;
	char *s, *dir, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
		sajesh_puts("HEY: >>getcwd CHECK THE ERROR<<\n");
	if (!sk_data->argv[1])
	{
		dir = sajesh_getenv(sk_data, "\"HOME\"=");
		if (!dir)
			chdir_ret =
				chdir((dir = sajesh_getenv(sk_data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (sajesh_strcmp(sk_data->argv[1], "-") == 0)
	{
		if (!sajesh_getenv(sk_data, "PREV-PWD="))
		{
			sajesh_puts(s);
			sajesh_putchar('\n');
			return (1);
		}
		sajesh_puts(sajesh_getenv(sk_data, "PREV-PWD=")), sajesh_putchar('\n');
		chdir_ret =
			chdir((dir = sajesh_getenv(sk_data, "PREV-PWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(sk_data->argv[1]);
	if (chdir_ret == -1)
	{
		sajesh_printError(sk_data, "unable to cd to ");
		sajesh_eputs(sk_data->argv[1]), sajesh_eputchar('\n');
	}
	else
	{
		sajesh_setEnv(sk_data, "PREV-PWD", sajesh_getenv(sk_data, "PWD="));
		sajesh_setEnv(sk_data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * sajesh_help - display help page
 * @sk_data: the date
 *
 *  Return: 0 value
 */
int sajesh_help(sk_data_t *sk_data)
{
	char **arg_array;

	arg_array = sk_data->argv;
	sajesh_puts("help page . some Function are yet to be implemented \n");
	if (0)
		sajesh_puts(*arg_array);
	return (0);
}
