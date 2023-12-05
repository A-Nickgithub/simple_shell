#include "shell.h"

/**
 * list_length - determines length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_length(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strg - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strg(list_t *head)
{
	list_t *node = head;
	size_t n = list_len(head), m;
	char **strs;
	char *strg;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		strg = malloc(_strlen(node->strg) + 1);
		if (!strg)
		{
			for (m = 0; m < n; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		strg = _strcpy(strg, node->str);
		strs[n] = strg;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_starts - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @chara: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts(list_t *node, char *prefix, char chara)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((chara == -1) || (*p == chara)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
