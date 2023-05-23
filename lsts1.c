#include "shell.h"

/**
 * get_nde_ind - gets the index of a node in the program
 * @hd: pointer to list head in program
 * @nde: pointer to the node in the program
 *
 * Return: index of node or -1 on success
 */
ssize_t get_nde_ind(list_t *hd, list_t *nde)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == nde)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}

/**
 * list_lens - determines length of linked list in the program
 * @h: pointer to first node in the program
 *
 * Return: size of list in the program
 */
size_t list_lens(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * lst_to_strs - returns an array of str of the lst->str
 * @hd: pointer to first node in the program
 *
 * Return: arr of strs
 */
char **lst_to_strs(list_t *hd)
{
	list_t *nde = hd;
	size_t j = list_lens(hd), k;
	char **stris;
	char *stri;

	if (!hd || !j)
		return (NULL);
	stris = malloc(sizeof(char *) * (j + 1));
	if (!stris)
		return (NULL);
	for (j = 0; nde; nde = nde->next, j++)
	{
		stri = malloc(_strlen(nde->str) + 1);
		if (!stri)
		{
			for (k = 0; k < j; k++)
				free(stris[k]);
			free(stris);
			return (NULL);
		}

		stri = _strcpy(stri, nde->str);
		stris[j] = stri;
	}
	stris[j] = NULL;
	return (stris);
}


/**
 * print_list - prints all elements of a list_t linked list in the program
 * @f: pointer to first node in the program
 *
 * Return: size of list
 */
size_t print_list(const list_t *f)
{
	size_t j = 0;

	while (f)
	{
		_puts(convert_number(f->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - returns node whose st starts with a prefix
 * @node: pointer to list head in the program
 * @pref: str to match in the program
 * @a: the next char after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *pref, char a)
{
	char *s = NULL;

	while (node)
	{
		s = starts_with(node->str, pref);
		if (s && ((a == -1) || (*s == a)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


