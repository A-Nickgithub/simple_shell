#include "shell.h"

/**
 * _env - prints the current environment
 * @inform: Structure containing potential arguments.
 * Return: Always 0
 */
int _env(inform_t *inform)
{
	print_list_str(inform->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inform: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(inform_t *inform, const char *name)
{
	list_t *node = inform->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @inform: Structure containing potential arguments
 *  Return: Always 0
 */
int _setenv(inform_t *inform)
{
	if (inform->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inform, inform->argv[1], inform->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - Remove an environment variable
 * @inform: Structure containing potential arguments.
 *  Return: Always 0
 */
int _unsetenv(inform_t *inform)
{
	int n;

	if (inform->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= inform->argc; n++)
		_unsetenv(inform, inform->argv[n]);

	return (0);
}

/**
 * pop_env_list - populates env linked list
 * @inform: Structure containing potential arguments.
 * Return: Always 0
 */
int pop_env_list(inform_t *inform)
{
	list_t *node = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_node_end(&node, environ[m], 0);
	inform->env = node;
	return (0);
}
