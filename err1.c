#include "shell.h"

/**
 * remove_comments - This func changes first instance of '#' with '\0'
 * @buff: address of the str to be modified
 *
 *
 * Return:  0;
 */
void remove_comments(char *buff)
{
	int s;

	for (s = 0; buff[s] != '\0'; s++)
		if (buff[s] == '#' && (!s || buff[s - 1] == ' '))
		{
			buff[s] = '\0';
			break;
		}
}

/**
 * _erratoi - changes a str to an int
 * @s: the str to be converted to int
 * Return: 0 if no numbers are in str, otherwise -1 on error
 */
int _erratoi(char *s)
{
	int c = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (c = 0;  s[c] != '\0'; c++)
	{
		if (s[c] >= '0' && s[c] <= '9')
		{
			res *= 10;
			res += (s[c] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - prints an err message
 * @info: the par & return info structure
 * @estr: string having specified err type
 * Return: 0 if no num in str, otherwise -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * convert_number - convert function
 * @num: num
 * @base: a base
 * @flags: argument flags of prog
 *
 * Return: str
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char s = 0;
	char *ptr;
	unsigned long r = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		r = -num;
		s = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[r % base];
		r /= base;
	} while (r != 0);

	if (s)
		*--ptr = s;
	return (ptr);
}

/**
 * print_d - function prints a decimal, number all in integers
 * @input: the input to take in
 * @fd: the filedescriptor to write to in the program
 *
 * Return: number of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, ct = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		ct++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + curr / j);
			ct++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	ct++;

	return (ct);
}
