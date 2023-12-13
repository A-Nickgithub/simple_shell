#include "shell.h"

/**
 * history_file - gets the history file
 * @inform: parameter struct
 * Return: allocated string containg history file
 */

char *history_file(inform_t *inform)
{
	char *buff, *direct;

	direct = _getenv(inform, "HOME=");
	if (!direct)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, direct);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * create_history - creates a file, or appends to an existing file
 * @inform: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int create_history(inform_t *inform)
{
	ssize_t filedes;
	char *filename = history_file(inform);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	filedes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (filedes == -1)
		return (-1);
	for (node = inform->history; node; node = node->next)
	{
		_putsfd(node->strg, filedes);
		_putfd('\n', filedes);
	}
	_putfd(BUF_FLUSH, filedes);
	close(filedes);
	return (1);
}

/**
 * read_history - reads history from file
 * @inform: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(inform_t *inform)
{
	int n, last = 0, linecount = 0;
	ssize_t filedes, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = history_file(inform);

	if (!filename)
		return (0);

	filedes = open(filename, O_RDONLY);
	free(filename);
	if (filedes == -1)
		return (0);
	if (!fstat(filedes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(filedes, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(filedes);
	for (n = 0; n < fsize; n++)
		if (buff[n] == '\n')
		{
			buff[n] = 0;
			build_history_list(inform, buff + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		build_history_list(inform, buff + last, linecount++);
	free(buff);
	inform->histcount = linecount;
	while (inform->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inform->history), 0);
	renumber_history(inform);
	return (inform->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @inform: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int build_history_list(inform_t *inform, char *buff, int linecount)
{
	list_t *node = NULL;

	if (inform->history)
		node = inform->history;
	add_node_end(&node, buff, linecount);

	if (!inform->history)
		inform->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @inform: Structure containing potential arguments.
 * Return: the new histcount
 */
int renumber_history(inform_t *inform)
{
	list_t *node = inform->history;
	int a = 0;

	while (node)
	{
		node->numb = a++;
		node = node->next;
	}
	return (inform->histcount = a);
}
