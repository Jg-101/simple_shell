#include "shell.h"

/**
 * input_buf - buffers chained commands in the prog
 * @info: parameter structure in the program
 * @buf: address of buffer in the program
 * @len: address of len variable of prog
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * read_buf - reads a buffer in the program
 * @info: parameter structure of the program
 * @buf: buffer of the program
 * @i: size
 *
 * Return: r if on success
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t l = 0;

	if (*i)
		return (0);
	l = read(info->readfd, buf, READ_BUF_SIZE);
	if (l >= 0)
		*i = l;
	return (l);
}

/**
 * get_input - gets a line minus the newline of the prog
 * @info: parameter structure of the program
 *
 * Return: bytes read in the prog
 */
ssize_t get_input(info_t *info)
{
	static char *buff; /* the ';' command chain  */
	static size_t a, b, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	g = input_buf(info, &buff, &len);
	if (g == -1) /* EOF */
		return (-1);
	if (len)
	{
		b = a;
		p = buff + a;

		check_chain(info, buff, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buff;
	return (r);

/**
 * _getline - gets the next line of input from STDIN in the program
 * @info: parameter structure in the program
 * @ptr: address of pointer to buffer, preallocated or NULL in the program
 * @length: size of initially allocated ptr buffer if not NULL
 *
 * Return: s if true
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUF_SIZE];
	static size_t a, len;
	size_t l;
	ssize_t r = 0, t = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		t = *length;
	if (a == len)
		a = len = 0;
	r = read_buf(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + a, '\n');
	l = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, t, t ? t + l : l + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (t)
		_strncat(new_p, buff + a, l - a);
	else
		_strncpy(new_p, buff + a, l - a + 1);
	t += l - a;
	a = l;
	p = new_p;
	if (length)
		*length = t;
	*ptr = p;
	return (t);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void if true
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

