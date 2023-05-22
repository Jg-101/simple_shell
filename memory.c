#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the addr in the program
 * @ptr: addr of the pointer to free in the program
 *
 * Return: 1 if freed, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
