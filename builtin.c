#include "shell.h"

/**
 * _myhelp - changes the working directory of the program
 * @info: Used to maintain const function prototype in shell prog.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}

/**
 * _mycd - changes the work directory of the program
 * @info: Used to maintain const function prototype in the shell prog.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *c, *dir, buffer[1024];
	int changdir_ret;

	c = getcwd(buffer, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			changdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			changdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		changdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		changdir_ret = chdir(info->argv[1]);
	if (changdir_ret == -1)
	{
		print_error(info, "cannot cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myexit - To exit the shell
 * @info: Used to maintain const function prototype.
 *  Return: exits with a given exit status
 */
int _myexit(info_t *info)
{
	int quitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		quitcheck = _erratoi(info->argv[1]);
		if (quitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

