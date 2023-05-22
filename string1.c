#include "shell.h"

/**
 *_puts - prints an inp str
 *@str: the str to be printed in the program
 *
 * Return: Nothing on SUCCESS
 */
void _puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _strcpy - copies a str
 * @dest: the destin
 * @src: the src
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a str
 * @str: the str to duplicate
 *
 * Return: pointer to the duplicated str
 */
char *_strdup(const char *str)
{
	int lngt = 0;
	char *rt;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lngt++;
	rt = malloc(sizeof(char) * (lngt + 1));
	if (!rt)
		return (NULL);
	for (lngt++; lngt--;)
		rt[lngt] = *--str;
	return (rt);
}

/**
 * _putchar - writes the char c to stdout in a program
 * @c: The char to print in the program
 *
 * Return: 1 on SUCCESS.
 * On error, -1 is returned, and errno is set app
 */
int _putchar(char c)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buff[j++] = c;
	return (1);
}
