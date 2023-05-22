#include "shell.h"

/**
 * _realloc - reallocates a block of memory in the program
 * @ptr: pointer to previous malloc'ated block in the program
 * @old_size: byte size of previous block in the program
 * @new_size: byte size of new block in the program
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	s = malloc(new_size);
	if (!s)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (s);
}

/**
 **_memset - fills mem with a const byte
 *@s: the pointer to the mem area in the program
 *@b: the byte to fill *s with in the prgram
 *@n: the amount of bytes to be filled in the program
 *Return: (s) a pointer to the memory area s Always
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - frees a str of strs
 * @pp: str of strs
 */
void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}


