#include "shell.h"

/**
 * clear_inform - initializes inform_t struct
 * @inform: struct address
 */
void clear_inform(inform_t *inform)
{
	inform->arg = NULL;
	inform->argv = NULL;
	inform->path = NULL;
	inform->argc = 0;
}

/**
 * set_inform - initializes info_t struct
 * @inform: struct address
 * @av: argument vector
 */
void set_inform(inform_t *inform, char **av)
{
	int n = 0;

	inform->fname = av[0];
	if (inform->arg)
	{
		inform->argv = strtow(inform->arg, " \t");
		if (!inform->argv)
		{

			inform->argv = malloc(sizeof(char *) * 2);
			if (inform->argv)
			{
				inform->argv[0] = _strdup(inform->arg);
				inform->argv[1] = NULL;
			}
		}
		for (n = 0; inform->argv && inform->argv[n]; n++)
			;
		inform->argc = n;

		replace_alias(inform);
		replace_var(inform);
	}
}

/**
 * free_inform - frees info_t struct fields
 * @inform: struct address
 * @all: true if freeing all fields
 */
void free_inform(inform_t *inform, int all)
{
	free_string(inform->argv);
	inform->argv = NULL;
	inform->path = NULL;
	if (all)
	{
		if (!inform->cmd_buf)
			free(inform->arg);
		if (inform->env)
			free_list(&(inform->env));
		if (inform->history)
			free_list(&(inform->history));
		if (inform->alias)
			free_list(&(inform->alias));
		free_string(inform->environ);
			inform->environ = NULL;
		my_free((void **)inform->cmd_buf);
		if (inform->readfd > 2)
			close(inform->readfd);
		_putchar(BUF_FLUSH);
	}
}
