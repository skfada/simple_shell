#include "sajesh.h"

/**
 * hsh - loop of the shell
 * @av: argument vectors
 * Return: 1 on failure 0 on success
 * @sk_data: linked data
 */
int hsh(sk_data_t *sk_data, char **av)
{
	int builtin_ret = 0;
	ssize_t read = 0;

	while (read != -1 && builtin_ret != -2)
	{
		sagesh_clearSkData(sk_data);
		if (sajesh_interactive(sk_data))
			sajesh_puts("$ ");
		sajesh_eputchar(BUF_FLUSH);
		read = get_input(sk_data);
		if (read != -1)
		{
			sagesh_setSkData(sk_data, av);
			builtin_ret = sagesh_findBuiltin(sk_data);
			if (builtin_ret == -1)
				sagesh_find_cmd(sk_data);
		}
		else if (sajesh_interactive(sk_data))
			sajesh_putchar('\n');
		sagesh_free_skData(sk_data, 0);
	}
	sagesh_writeHist(sk_data);
	sagesh_free_skData(sk_data, 1);
	if (!sajesh_interactive(sk_data) && sk_data->status)
		exit(sk_data->status);
	if (builtin_ret == -2)
	{
		if (sk_data->err_num == -1)
			exit(sk_data->status);
		exit(sk_data->err_num);
	}
	return (builtin_ret);
}

/**
 * sagesh_findBuiltin - locate built in commabn
 * Return: 0 for success, 1 on faileure 2 on signal exit
 * @sk_data: linked data
 */
int sagesh_findBuiltin(sk_data_t *sk_data)
{
	int built_in_ret = -1;
	int index;

	builtin_table builtintbl[] = {
		{"exit", sajesh_exit},
		{"env", sajesh_env},
		{"help", sajesh_help},
		{"history", sajesh_hist},
		{"setenv", _sajeshSetEnv},
		{"unsetenv", _sajeshUnsetEnv},
		{"cd", sajesh_cd},
		{"alias", sajesh_alias},
		{NULL, NULL}
	};

	for (index = 0; builtintbl[index].type; index++)
		if (sajesh_strcmp(sk_data->argv[0], builtintbl[index].type) == 0)
		{
			sk_data->line_count++;
			built_in_ret = builtintbl[index].func(sk_data);
			break;
		}
	return (built_in_ret);
}

/**
 * sagesh_find_cmd - locate command
 * Return: none
 * @sk_data: linked dat
 */
void sagesh_find_cmd(sk_data_t *sk_data)
{
	char *path = NULL;
	int count;
	int index;

	sk_data->path = sk_data->argv[0];
	if (sk_data->linecount_flag == 1)
	{
		sk_data->line_count++;
		sk_data->linecount_flag = 0;
	}
	for (index = 0, count = 0; sk_data->arg[index]; index++)
		if (!sajesh_isDelim(sk_data->arg[index], " \t\n"))
			count++;
	if (!count)
		return;

	path = sajesh_findPath(sk_data,
			sajesh_getenv(sk_data, "PATH="), sk_data->argv[0]);
	if (path)
	{
		sk_data->path = path;
		sagesh_fork_cmd(sk_data);
	}
	else
	{
		if ((sajesh_interactive(sk_data) || sajesh_getenv(sk_data, "PATH=")
			|| sk_data->argv[0][0] == '/') && sajesh_isCmd(sk_data, sk_data->argv[0]))
			sagesh_fork_cmd(sk_data);
		else if (*(sk_data->arg) != '\n')
		{
			sk_data->status = 127;
			sajesh_printError(sk_data, "not found\n");
		}
	}
}

/**
 * sagesh_fork_cmd - create the process for executing command
 * Return: none
 * @sk_data: linked data
 */
void sagesh_fork_cmd(sk_data_t *sk_data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("just dey play:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(sk_data->path, sk_data->argv, sajesh_getEnviron(sk_data)) == -1)
		{
			sagesh_free_skData(sk_data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(sk_data->status));
		if (WIFEXITED(sk_data->status))
		{
			sk_data->status = WEXITSTATUS(sk_data->status);
			if (sk_data->status == 126)
				sajesh_printError(sk_data, "Access denied\n");
		}
	}
}
