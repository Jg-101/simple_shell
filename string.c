#include "shell.h"

/**
 * _strlen - returns the length of a str
 * @s: the str whose length to check in the program
 *
 * Return: int length of str on SUCCESS
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two str.
 * @s1: the first str
 * @s2: the second str
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero on else
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _strcat - concat two str
 * @dest: the destination buffer of the program
 * @src: the source buffer of the program
 *
 * Return: pointer to destination buffer on SUCCESS
 */
char *_strcat(char *dest, char *src)
{
	char *rt = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (rt);
}

/**
 * starts_with - checks if needle starts with haystack in the program
 * @haystack: str to search in the program
 * @needle: the substr to find in the program
 *
 * Return: addr of next char of haystack or NULL on SUCCESS
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

