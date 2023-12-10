#include "shell.h"

/**
 * myexi - exits the shell
 * @inform: Struct containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if inform.argv[0] != "exit"
 */
int myexi(inform_t *inform)
{
	int ex;

	if (inform->argv[1])
	{
		ex = _erratoi(inform->argv[1]);
		if (ex == -1)
		{
			inform->status = 2;
			print_error(inform, "Illegal number: ");
			_eputs(inform->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inform->err_num = _erratoi(inform->argv[1]);
		return (-2);
	}
	inform->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the cd of the process
 * @inform: Structure containing potential arguments.
 *  Return: Always 0
 */
int _cd(inform_t *inform)
{
	char *s, *direct, buffer[1024];
	int chdirect_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inform->argv[1])
	{
		direct = _getenv(inform, "HOME=");
		if (!direct)

		chdirect_ret =
			chdir((direct = _getenv(inform, "PWD=")) ? direct : "/");
		else
			chdirect_ret = chdir(direct);
	}
	else if (_strcmp(inform->argv[1], "-") == 0)
	{
		if (!_getenv(inform, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inform, "OLDPWD=")), _putchar('\n');
		chdirect_ret =
			chdir((direct = _getenv(inform, "OLDPWD=")) ? direct : "/");
	}
	else
		chdirect_ret = chdir(inform->argv[1]);
	if (chdirect_ret == -1)
	{
		print_error(inform, "can't cd to ");
		_eputs(inform->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
		_setenv(inform, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the cd of the process
 * @inform: Structure containing potential arguments.
 *  Return: Always 0
 */
int _help(inform_t *inform)
{
	char **arg_array;

	arg_array = inform->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
