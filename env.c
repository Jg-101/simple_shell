#include "shell.h"

/**
 * populate_env_list - populates environment linked lists
 * @info: Structure containing potential arguments in the program.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}

/**
 * _myenv - prints the current working environment
 * @info: Structure containing potential arguments in program.
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments in prog.
 * @name: enviroment variable name
 *
 * Return: the value inputted
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *d;

	while (node)
	{
		d = starts_with(node->str, name);
		if (d && *d)
			return (d);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable in the prog
 * @info: Structure containing potential arguments in the program.
 *  Return:  0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}



/**
 * _myunsetenv - Remove an environment variable in the program
 * @info: Structure containing potential arguments in the program.
 *  Return: 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("insuffecient arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}


