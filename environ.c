#include "shell.h"
/**
 * _getenv - gets the environ variable
 * @name: name of the env variabl to look for
 * Return: pointer to the env variable
 **/
char *_getenv(char *name)
{
	int a = 0;
	char *token, *delm = "=";
	char *dupe;

	while (environ[a] != NULL)
	{
		dupe = _strdup(environ[a]);
		token = _strtok(environ[a], delm);
		if (_strcmp(token, name) == 0)
		{
			token = _strtok(NULL, delm);
			environ[a] = _strcpy(environ[a], dupe);
			free(dupe);
			return (token);
		}
		environ[a] = _strcpy(environ[a], dupe);
		free(dupe);
		a++;
	}
	return (0);
}
/**
 * _printenv - prints the enviroment
 * @argv: pointer to the commands
 * Return: 1 on success
 */
int _printenv(char **argv)
{
	int a;
	(void) argv;

	for (a = 0; *environ[a] != '\0'; a++)
	{
		_puts(environ[a]);
		_puts("\n");
	}
	return (0);
}
/**
 * _setenv - sets a new enviromental variable
 * @argv: pointer to the input commands
 * Return: 1 on success
 */
int _setenv(char **argv)
{
	int status = EXIT_SUCCESS, exist = 0, a = 0;
	char *dupe = 0, *tok = 0, *val = 0;

	while (environ[a])
	{
		dupe = _strdup(environ[a]);
		tok = _strtok(dupe, "=");
		if (!_strcmp(tok, argv[1]))
		{
			tok = _strcat(argv[1], "=");
			val = _strcat(tok, argv[2]);

			environ[a] = _strcpy(environ[a], val);
			free(tok);
			free(val);
			exist = 1;
		}
		free(dupe);
		a++;
	}

	/* if the variable does not exist then create it */

	if (!exist)
	{
		/* not implemented */
	}

	return (status);
}
/**
 * _unsetenv - unsets an enviromental var
 * @argv: pointer to the buffer with the command line
 * Return: 1 on success
 */
int _unsetenv(char **argv)
{
	int a = 0, exist = 0, len = 0, b = 0;
	char *tok, *copy;
	char **new_env;

	while (environ[a])
	{
		copy = _strdup(environ[a]);
		tok = _strtok(copy, "=");
		if (!_strcmp(tok, argv[1]))
		{
			exist = 1;
		}
		len++;
		a++;
		free(copy);
	}

	if (exist)
	{
		new_env = malloc(sizeof(char *) * (len - 1));
		for (a = 0; a < len; a++)
		{
			copy = _strdup(environ[a]);
			tok = _strtok(copy, "=");
			if (!_strcmp(tok, argv[1]))
			{
				printf("-------------> Removing: %s\n", environ[a]);
				continue;
			}
			new_env[b] = environ[a];
			b++;
		}
		new_env[len - 1] = NULL;
		environ = new_env;
	}
	return (1);
}
/**
 * _non_int - executes the shell in non-interactive mode
 * @arr: array of structures to handle built in commands
 */
void _non_int(built_in_t arr[])
{
	char **argv;
	char *buff = 0;
	int status = EXIT_SUCCESS;
	size_t buffsize = 1024;
	int err_count = 0;

	while (getline(&buff, &buffsize, stdin) != EOF)
	{
		err_count++;
		argv = token_buff(buff, " \t\r\n\a");
		status = shell_execute(argv, arr);
		free(argv);
	}
	free(buff);
	exit(status);
}
