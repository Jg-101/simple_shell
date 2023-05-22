#include "shell.h"

/**
 * main - entry point of prog
 * @ac: arg count of prog
 * @av: arg vector of prog
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int rd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (rd)
		: "r" (rd));

	if (ac == 2)
	{
		rd = open(av[1], O_RDONLY);
		if (rd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readrd = rd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
