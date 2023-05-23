#include "shell.h"

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int j, built_in_rt = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
		{
			info->line_count++;
			built_in_rt = builtintbl[j].func(info);
			break;
		}
	return (built_in_rt);
}

/**
 * hsh - main shell loop in the program
 * @info: the parameter & return information structure
 * @av: the argument vector from main() in the program
 *
 * Return: 0 on success, 1 on error, or error code inserted
 */
int hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int builtin_rt = 0;

	while (s != -1 && builtin_rt != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(info);
		if (s != -1)
		{
			set_info(info, av);
			builtin_rt = find_builtin(info);
			if (builtin_rt == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_rt == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_rt);
}


/**
 * fork_cmd - forks a an exec thread to run cmd in the program
 * @info: the parameter & return info structure
 *
 * Return: void on SUCCESS
 */
void fork_cmd(info_t *info)
{
	pid_t child_pd;

	child_pd = fork();
	if (child_pd == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pd == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
/**
 * find_cmd - finds a command in PATH in the program
 * @info: the parameter & return info structure
 *
 * Return: void on SUCCESS
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int r, t;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (r = 0, t = 0; info->arg[r]; r++)
		if (!is_delim(info->arg[r], " \t\n"))
			t++;
	if (!t)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}
