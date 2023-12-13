#include "shell.h"
/**
 * myexit - checks whether the input is the exit command
 * @argv: buffer with the commands
 * Return: Exit status
 */
int myexit(char **argv)
{
	int status = 0, a;

	if (argv[1] == NULL)
	{
		free(argv[0]);
		free(argv);
		fflush(stdout);
		exit(status);
	}

	for (a = 0; argv[1][a] != '\0'; a++)
	{
		if (argv[1][a] < 48 || argv[1][a] > 57)
			return (3);
	}
	status = atoi(argv[1]);
	free(argv[0]);
	free(argv);
	exit(status);
}
/**
 * _cd - function that changes the current directory
 * @argv: string containing the input
 * Return: 1 on success
 **/
int _cd(char **argv)
{
	char buff[1024], *cwd, *new_wd, *comp = "-", *old_pwd;
	int chi = 0;
	char *env;

	cwd = getcwd(buff, sizeof(buff));
	if (argv[1] == NULL)
	{
		setenv("OLDPWD", getcwd(buff, sizeof(buff)), 1);
		env = _getenv("HOME");
		chdir(env);
		return (0);
	}
	if (_strcmp(argv[1], comp) == 0)
	{
		old_pwd = _getenv("OLDPWD");
		setenv("OLDPWD", getcwd(buff, sizeof(buff)), 1);
		chdir(old_pwd);
		return (0);
	}

	if (cwd == NULL)
	{
		free(argv);
		perror("Error: ");
		return (1);
	}

	chi = chdir(argv[1]);

	if (chi == -1)
	{
		free(argv);
		perror("Error: ");
		return (1);
	}
	setenv("OLDPWD", _getenv("PWD"), 1);
	new_wd = getcwd(buff, sizeof(buff));
	setenv("PWD", new_wd, 1);
	return (0);
}
