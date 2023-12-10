#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inform: Structure containing potential arg
 *  Return: Always 0
 */
int _history(inform_t *inform)
{
	print_list(inform->history);
	return (0);
}

/**
 * set_alias - sets alias to string
 * @inform: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(inform_t *inform, char *strg)
{
	char *p, y;
	int r;

	p = _strchr(strg, '=');
	if (!p)
		return (1);
	y = *p;
	*p = 0;
	r = delete_node_at_index(&(inform->alias),
		node_index(inform->alias, node_starts(inform->alias, strg, -1)));
	*p = y;
	return (r);
}

/**
 * set2_alias - sets alias to string
 * @inform: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set2_alias(inform_t *inform, char *strg)
{
	char *p;

	p = _strchr(strg, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (set_alias(inform, strg));

	set_alias(inform, strg);
	return (add_node_end(&(inform->alias), strg, 0) == NULL);
}

/**
 * prt_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int prt_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->strg, '=');
		for (a = node->strg; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * mainalias - mimics the alias builtin
 * @inform: Structure containing potential arguments.
 *  Return: Always 0
 */
int mainalias(inform_t *inform)
{
	int n = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inform->argc == 1)
	{
		node = inform->alias;
		while (node)
		{
			prt_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (n = 1; inform->argv[n]; n++)
	{
		p = _strchr(inform->argv[n], '=');
		if (p)
			set2_alias(inform, inform->argv[n]);
		else
			prt_alias(node_starts(inform->alias, inform->argv[n], '='));
	}

	return (0);
}
