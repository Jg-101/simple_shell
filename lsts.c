#include "shell.h"

/**
 * free_list - frees all the nodes of a list in the program
 * @head_ptr: addr of pointer in the head node
 *
 * Return: void Always
 */
void free_list(list_t **head_ptr)
{
	list_t *nde, *next_nde, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	nde = hd;
	while (nde)
	{
		next_nde = nde->next;
		free(nde->str);
		free(nde);
		nde = next_nde;
	}
	*head_ptr = NULL;
}

/**
 * add_node - adds a node to the start of the list in the program
 * @head: addr of pointer to head node in the program
 * @str: string field of node in the program
 * @num: node index used by history in the program
 *
 * Return: size of list Always
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}

/**
 * add_node_end - adds a node to the end of the list in the program
 * @head: addr of pointer to head node
 * @str: str field of node
 * @num: node index used by history in the program
 *
 * Return: size of list Always
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_nde, *nde;

	if (!head)
		return (NULL);

	nde = *head;
	new_nde = malloc(sizeof(list_t));
	if (!new_nde)
		return (NULL);
	_memset((void *)new_nde, 0, sizeof(list_t));
	new_nde->num = num;
	if (str)
	{
		new_nde->str = _strdup(str);
		if (!new_nde->str)
		{
			free(new_nde);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_nde;
	}
	else
		*head = new_nde;
	return (new_nde);
}



/**
 * print_list_str - prnts only the str elem of a list_t linked list in the prg
 * @h: pointer to first node
 *
 * Return: size of list Always
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - del node at given index in the program
 * @head: addr of pointer to first node in the program
 * @index: index of node to del in prog
 *
 * Return: 1 on success, on failre 0
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *nde, *prev_nde;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		nde = *head;
		*head = (*head)->next;
		free(nde->str);
		free(nde);
		return (1);
	}
	nde = *head;
	while (nde)
	{
		if (j == index)
		{
			prev_nde->next = nde->next;
			free(nde->str);
			free(nde);
			return (1);
		}
		j++;
		prev_nde = nde;
		nde = nde->next;
	}
	return (0);
}


