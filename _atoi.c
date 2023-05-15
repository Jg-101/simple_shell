#include "shell.h"

/**
 * interactive - returns true if shell is active
 * @info: This contains structure address
 *
 * Return: 1 if mode is interactive, else 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @a: the char to check
 * @delim: the delimeter string to be used
 * Return: 1 if true,and 0 if false
 */
int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic char
 *@a: The char to put in
 *Return: 1 if a is alphabetic, and 0 if false
 */

int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a str to an int
 *@r: the str to be converted
 *Return: 0 if no numbers are in str, show converted num if not
 */

int _atoi(char *r)
{
	int b, s = 1, fl = 0, out;
	unsigned int res = 0;

	for (b = 0;  r[b] != '\0' && fl != 2; b++)
	{
		if (r[b] == '-')
			s *= -1;

		if (r[b] >= '0' && r[b] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (r[b] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}

	if (s == -1)
		out = -res;
	else
		out = res;

	return (out);
}
