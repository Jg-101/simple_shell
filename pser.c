#include "shell.h"

/**
 * is_cmd - determines if a file is an exec command in the prog
 * @info: the info structure of the program
 * @path: path to the file in the prog
 *
 * Return: 1 if true, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sti;

	(void)info;
	if (!path || stat(path, &sti))
		return (0);

	if (sti.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * find_path - finds this cmd in the PATH string in the program
 * @info: the info structure of the program
 * @pathstr: the PATH string of the program
 * @cmd: the cmd to find in the program
 *
 * Return: full path of cmd if found or NULL if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_post = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_post, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_post = j;
		}
		j++;
	}
	return (NULL);
}

/**
 * dup_chars - duplicates characters in the program
 * @pathstr: the PATH string in the program
 * @start: starting index of the program
 * @stop: stopping index of the program
 * Return: pointer to new buffer in the program
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int r = 0, s = 0;

	for (s = 0, r = start; r < stop; r++)
		if (pathstr[r] != ':')
			buff[s++] = pathstr[r];
	buff[s] = 0;
	return (buff);
}


