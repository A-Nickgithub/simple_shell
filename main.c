#include "shell.h"
/**
 * main - integrates the functions to make the shell work
 * Return: 0 on success
 */
int main(void)
{
	char *buff = NULL, **argv = NULL;
	int flags = 1;

	int status = EXIT_SUCCESS;

	built_in_t built_in_arr[] = {
		{"exit", myexit},
		{"env", _printenv},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{NULL, NULL}
	};

	if (isatty(STDIN_FILENO) != 1)
	{
		_non_int(built_in_arr);
	}

	(void)signal(SIGINT, sign_handler);
	(void) built_in_arr;

	while (flags)
	{
		_puts("$ ");


		buff = read_input();

		argv = token_buff(buff, " \t\r\n\a");

		status = shell_execute(argv, built_in_arr);

		free(argv);
		free(buff);
	}
	return (status);
}
/**
 * token_buff - splits the buffer into tokens
 * @buff: pointer to the buffer
 * @delimit: delimitator chosen
 * Return: double pointer to the tokens
 **/
char **token_buff(char *buff, char *delimit)
{
	int buffsize = 64, iterator = 0;
	char **tokens = malloc(sizeof(char *) * buffsize);
	char *stoken;

	if (tokens == NULL)
	{
		perror("Not possible to allocate memory");
		free(buff);
		exit(98);
	}
	stoken = _strtok(buff, delimit);
	while (stoken != NULL)
	{
		tokens[iterator] = stoken;
		iterator++;
		stoken = _strtok(NULL, delimit);
	}
	tokens[iterator] = NULL;
	return (tokens);
}

/**
 * read_input - read input form stdin
 * Return: pointer to buffer read
 */
char *read_input()
{
	char *buff = NULL;
	size_t size = 1024;

	if (getline(&buff, &size, stdin) == EOF)
	{
		_puts("\n");
		free(buff);
		exit(127);
	}
	buff[_strlen(buff) - 1] = '\0';
	return (buff);
}

/**
 * sign_handler - handles the abscensce of a sign
 * @i: integer
 */
void sign_handler(int i)
{
	(void) i;
	_puts("\n");
	puts("$ ");
	fflush(stdout);
}
