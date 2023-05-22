#include "shell.h"

/**
 * replace_string - replaces old str
 * @past: contains addr of old str
 * @anew: new str that replaces old str
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_string(char **past, char *anew)
{
	free(*past);
	*past = anew;
	return (1);
}

/**
 * is_chain - test if curr character in buffer is a chain delimeter in the program
 * @inf: the parameter structure of the program
 * @buff: the character buffer of the program
 * @t: addr of curr position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *buff, size_t *t)
{
	size_t i = *t;

	if (buff[i] == '|' && buff[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[i] == '&' && buff[i + 1] == '&')
	{
		buff[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[i] == ';')
		buff[i] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*t = i;
	return (1);
}



/**
 * replace_alias - replaces an aliases in the tokenized str in the program
 * @inf: the parameter structure of the program
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_alias(info_t *inf)
{
	int j;
	list_t *nde;
	char *p;

	for (j = 0; j < 10; j++)
	{
		nde = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!nde)
			return (0);
		free(inf->argv[0]);
		p = _strchr(nde->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @inf: the parameter structure
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @inf: the parameter structure
 * @buff: the char buffer
 * @tp: address of current position in buff
 * @i: starting position in buff
 * @len: length of buff
 *
 * Return: Void
 */
void check_chain(info_t *inf, char *buff, size_t *tp, size_t i, size_t len)
{
	size_t j = *tp;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = len;
		}
	}

	*tp = j;
