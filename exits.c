#include "shell.h"

/**
 **_strchr - locates a char in a str
 *@s: the str to be parsed in the program
 *@c: the char to look for in the program
 *Return: (s) a pointer to the mem area s in the prog
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}



/**
 **_strncat - concatenates two str
 *@dest: the first str
 *@src: the second str
 *@n: the amount of bytes to be max used
 *Return: the concatenated str
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *c = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (c);
}

/**
 **_strncpy - copy a str
 *@dest: the destin str to be copied to in the prog
 *@src: the source str
 *@n: the amount of char to be copied in the prog
 *Return: the concatenated str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *c = dest;

	i = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (c);
}
