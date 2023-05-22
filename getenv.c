#include "shell.h"

/**
 * get_environ - returns the str arr cpy of our env
 * @info: Struct containing potential arguments.
 * Return: 0 Always
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _setenv - Initializes a new env var in the program
 * @info: Struct containing potential arguments in the program.
 * @var: the string environ variable attributes
 * @value: the string enviroment variable value
 *  Return: 0 Always
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *t;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = info->env;
	while (node)
	{
		t = starts_with(node->str, var);
		if (t && *t == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - Remove an env var in the program
 * @info: Structure containing arising or possible arguments
 *  Return: 1 on delete, otherwise return 0
 * @var: the str env var property odf the program
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t j = 0;
	char *t;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (t && *t == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), j);
			j = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (info->env_changed);
}

