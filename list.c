#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @strg: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *strg, int numb)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (strg)
	{
		new_head->strg = _strdup(strg);
		if (!new_head->strg)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @strg: str field of node
 * @numb: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *strg, int numb)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (strg)
	{
		new_node->strg = _strdup(strg);
		if (!new_node->strg)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->strg ? h->strg : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @ind: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int ind)
{
	list_t *node, *prev_node;
	unsigned int n = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->strg);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (n == ind)
		{
			prev_node->next = node->next;
			free(node->strg);
			free(node);
			return (1);
		}
		n++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->strg);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
