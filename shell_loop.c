#include "shell.h"

/**
 * hsh - main shell loop
 * @inform: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(inform_t *inform, char **av)
{
	ssize_t c = 0;
	int builtin_ret = 0;

	while (c != -1 && builtin_ret != -2)
	{
		clear_inform(inform);
		if (interact(inform))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		c = get_input(inform);
		if (c != -1)
		{
			set_inform(inform, av);
			builtin_ret = find_builtin(inform);
			if (builtin_ret == -1)
				find_cmd(inform);
		}
		else if (interact(inform))
			_putchar('\n');
		free_inform(inform, 0);
	}
	create_history(inform);
	free_inform(inform, 1);
	if (!interact(inform) && inform->status)
		exit(inform->status);
	if (builtin_ret == -2)
	{
		if (inform->err_num == -1)
			exit(inform->status);
		exit(inform->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @inform: the parameter & return info struct
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(inform_t *inform)
{
	int n, built_in_ret = -1;
	builtin_table builtintbl[] =
	{
		{"exit", myexi},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintbl[n].type; n++)
		if (_strcmp(inform->argv[0], builtintbl[n].type) == 0)
		{
			inform->line_count++;
			built_in_ret = builtintbl[n].func(inform);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inform: the parameter & return info struct
 * Return: void
 */
void find_cmd(inform_t *inform)
{
	char *path = NULL;
	int n, k;

	inform->path = inform->argv[0];
	if (inform->linecount_flag == 1)
	{
		inform->line_count++;
		inform->linecount_flag = 0;
	}
	for (n = 0, k = 0; inform->arg[n]; n++)
		if (!is_delm(inform->arg[n], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(inform, _getenv(inform, "PATH="), inform->argv[0]);
	if (path)
	{
		inform->path = path;
		fork_cmd(inform);
	}
	else
	{
		if ((interact(inform) || _getenv(inform, "PATH=")
			|| inform->argv[0][0] == '/') && is_exec(inform, inform->argv[0]))
			fork_cmd(inform);
		else if (*(inform->arg) != '\n')
		{
			inform->status = 127;
			print_error(inform, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inform: the parameter & return info struct
 * Return: void
 */
void fork_cmd(inform_t *inform)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inform->path, inform->argv, getenv(inform)) == -1)
		{
			free_inform(inform, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inform->status));
		if (WIFEXITED(inform->status))
		{
			inform->status = WEXITSTATUS(inform->status);
			if (inform->status == 126)
				print_error(inform, "Permission denied\n");
		}
	}
}
