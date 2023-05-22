#include "shell.h"

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t rd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	rd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (rd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, rd);
		_putfd('\n', rd);
	}
	_putfd(BUF_FLUSH, rd);
	close(rd);
	return (1);
}

/**
 * get_history_file - gets the history of file in program
 * @info: parameter struct
 *
 * Return: allocated string containg history file in program
 */

char *get_history_file(info_t *info)
{
	char *buff, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * renumber_history - renums the hist linked list after the changes in the prog
 * @info: Structure containing potential arguments in the program
 * Return: the new histcount of the program
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}

/**
 * read_history - reads history from file in the program
 * @info: the parameter structure of the program
 *
 * Return: histcount on success, otherwise return 0
 */
int read_history(info_t *info)
{
	int j, lst = 0, lincount = 0;
	ssize_t rd, tdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	rd = open(filename, O_RDONLY);
	free(filename);
	if (rd == -1)
		return (0);
	if (!fstat(rd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	tdlen = read(rd, buff, fsize);
	buff[fsize] = 0;
	if (tdlen <= 0)
		return (free(buff), 0);
	close(rd);
	for (j = 0; j < fsize; j++)
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(info, buff + lst, lincount++);
			lst = j + 1;
		}
	if (lst != j)
		build_history_list(info, buff + lst, lincount++);
	free(buff);
	info->histcount = lincount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds an entry to a history linked list in the program
 * @info: Struct containing potential arguments
 * @buf: buffer for the program
 * @linecount: the history linecount, histcount for the program
 *
 * Return: 0 Always
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


