#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info: Structure containing potential arguments
 *  Return:  0 on functionality
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias - sets alias to string
 * @info: parameter structure for program
 * @st: the string alias to be used for the program
 *
 * Return: Display 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *st)
{
	char *a, b;
	int sit;

	a = _strchr(st, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	sit = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, st, -1)));
	*a = b;
	return (sit);
}

/**
 * set_alias - sets alias to string in the program
 * @info: parameter structure
 * @str: the string alias of the program
 *
 * Return: Always 0 on functionality, and 1 on errors
 */
int set_alias(info_t *info, char *str)
{
	char *j;

	j = _strchr(str, '=');
	if (!j)
		return (1);
	if (!*++j)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}



/**
 * print_alias - prints an alias str in the program
 * @node: the alias node to be used
 *
 * Return: Always 0 on functionality, and 1 on error
 */
int print_alias(list_t *node)
{
	char *j = NULL, *b = NULL;

	if (node)
	{
		j = _strchr(node->str, '=');
		for (b = node->str; b <= j; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(j + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - acts as the otherwise builtin
 * @info: Structure containing all potential arguments.
 *  Return:  0
 */
int _myalias(info_t *info)
{
	int s = 0;
	char *j = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (s = 1; info->argv[s]; s++)
	{
		j = _strchr(info->argv[s], '=');
		if (j)
			set_alias(info, info->argv[s]);
		else
			print_alias(node_starts_with(info->alias, info->argv[s], '='));
	}

	return (0);
}
