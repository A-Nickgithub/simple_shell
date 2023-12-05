#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@x: the pointer to the memory area
 *@y: the byte to fill *s with
 *@z: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *x, char y, unsigned int z)
{
	unsigned int n;

	for (n = 0; n < z; n++)
		x[n] = y;
	return (x);
}

/**
 * free_string - frees a string of strings
 * @pp: string of strings
 */
void free_string(char **pp)
{
	char **n = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(n);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_block: byte size of previous block
 * @curr_block: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int prev_block, unsigned int curr_block)
{
	char *p;

	if (!ptr)
		return (malloc(curr_block));
	if (!curr_block)
		return (free(ptr), NULL);
	if (curr_block == prev_block)
		return (ptr);

	p = malloc(curr_block);
	if (!p)
		return (NULL);

	prev_block = prev_block < curr_block ? prev_block : curr_block;
	while (prev_block--)
		p[prev_block] = ((char *)ptr)[prev_block];
	free(ptr);
	return (p);
}
