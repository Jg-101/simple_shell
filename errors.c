#include "shell.h"

/**
 * _eputchar - writes the char c to stderr
 * @c: The character to be printed
 *
 * Return: 1 if successfully.
 * On error, -1 is brought back, and errno is set correctly.
 */
int _eputchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 *_eputs - prints an input string, inputed in the program
 * @str: the str to be printed in the prog
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int s = 0;

	if (!str)
		return;
	while (str[s] != '\0')
	{
		_eputchar(str[s]);
		s++;
	}
}



/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}

/**
 *_putsfd - prints an inp str
 * @str: the string to be printed in the program
 * @fd: the file descriptor to write to write to in the proogram
 *
 * Return: the number of characters inputted
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
