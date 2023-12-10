#include "shell.h"

/**
 * get_environment - returns the string array copy of our environ
 * @inform: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_environment(inform_t *inform)
{
	if (!inform->environ || inform->env_changed)
	{
		inform->environ = list_to_strg(inform->env);
		inform->env_changed = 0;
	}

	return (inform->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inform: Structure containing potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(inform_t *inform, char *var)
{
	list_t *node = inform->env;
	size_t n = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->strg, var);
		if (p && *p == '=')
		{
			inform->env_changed = delete_node_at_index(&(inform->env), n);
			n = 0;
			node = inform->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (inform->env_changed);
}

/**
 * _setenv - Initialize a new environment variable
 * @inform: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(inform_t *inform, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = inform->env;
	while (node)
	{
		p = starts_with(node->strg, var);
		if (p && *p == '=')
		{
			free(node->strg);
			node->strg = buff;
			inform->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inform->env), buff, 0);
	free(buff);
	inform->env_changed = 1;
	return (0);
}
