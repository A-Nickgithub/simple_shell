#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @inform: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(inform_t *inform, char *buff, size_t *p)
{
	size_t b = *p;

	if (buff[b] == '|' && buff[b + 1] == '|')
	{
		buff[b] = 0;
		b++;
		inform->cmd_buf_type = CMD_OR;
	}
	else if (buff[b] == '&' && buff[b + 1] == '&')
	{
		buff[b] = 0;
		b++;
		inform->cmd_buf_type = CMD_AND;
	}
	else if (buff[b] == ';')
	{
		buff[b] = 0;
		inform->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inform: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buff
 * Return: Void
 */
void check_chain(inform_t *inform, char *buff, size_t *p, size_t i, size_t len)
{
	size_t b = *p;

	if (inform->cmd_buf_type == CMD_AND)
	{
		if (inform->status)
		{
			buff[i] = 0;
			b = len;
		}
	}
	if (inform->cmd_buf_type == CMD_OR)
	{
		if (!inform->status)
		{
			buff[i] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @inform: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(inform_t *inform)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts(inform->alias, inform->argv[0], '=');
		if (!node)
			return (0);
		free(inform->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inform->argv[0] = p;
	}
	return (1);
}

/**
 * replace_var - replaces var in the tokenized string
 * @inform: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_var(inform_t *inform)
{
	int a = 0;
	list_t *node;

	for (a = 0; inform->argv[a]; a++)
	{
		if (inform->argv[a][0] != '$' || !inform->argv[a][1])
			continue;

		if (!_strcmp(inform->argv[a], "$?"))
		{
			replace_string(&(inform->argv[a]),
				_strdup(convert_number(inform->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inform->argv[a], "$$"))
		{
			replace_string(&(inform->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts(inform->env, &inform->argv[a][1], '=');
		if (node)
		{
			replace_string(&(inform->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inform->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @prev: address of old string
 * @curr: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **prev, char *curr)
{
	free(*prev);
	*prev = curr;
	return (1);
}
