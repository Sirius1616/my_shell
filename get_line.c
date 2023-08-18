#include "shell.h"

/**
 * insert_buf - chained commands of buffer
 * @details: structural parameter
 * @buffer: buffer's address
 * @size: len var address
 *
 * Return: read bytes
 */


ssize_t insert_buf(t_info *details, char **buffer, size_t *size)
{
	ssize_t r = 0;
	size_t len_pt = 0;

	if (*len == 0)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleCtrlC);

		#if GETLN_USE
			r = getline(buffer, &len_pt, stdin);
		#else
			r = get_line(details, buffer, &len_pt);
		#endif

		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}

			details->count_line_flag = 1;
			comment_rem(*buffer);
			hist_build(details, *buffer, details->histcnt++);

			{
				*len = r;
				details->cmd_ads = buffer;
			}
		}
	}

	return (r);
}



/**
 * find_input - finds a line
 * @details: structural parameter
 *
 * Return: bytes read
 */

ssize_t find_input(t_info *details)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t q = 0;
	char **buf_pt = &(details->ag), *pt;

	_putchar(BUFFER_FLUSH);
	q = insert_buf(details, &buffer, &len);

	if (q == -1)
	return (-1);

	if (len)
	{
		j = i;
		pt = buffer + i;

		chk_link(details, buffer, &j, i, len);

		for (; j < len; j++)
	{
		if (is_linked(details, buffer, &j))
		break;
	}

	i = j + 1;
	if (i >= len)
	{
		i = len = 0;
		details->cmd_type = NORM_CMD;
	}

	*buf_pt = pt;
	return (_strlen(pt));
	}

	*buf_pt = buffer;
	return (q);
}


/**
 * rd_buffer - buffer is read
 * @details: structural parameter
 * @buffer: buffer
 * @j: size
 *
 * Return: q
 */

ssize_t rd_buffer(t_info *details, char *buffer, size_t *j)
{
	ssize_t q = 0;

	if (*j == 0)
	{
		q = read(details->read_file_desc, buffer, RD_BUFFER_SZ);
		if (q >= 0)
		{
			*j = q;
		}
	}

	return (q);
}



/**
 * get_line - finds the next line
 * @details: structural parameter
 * @ptr: pointer to buffer address
 * @length: size of prev pointer buffer
 *
 * Return: s
 */

int get_line(t_info *details, char **ptr, size_t *length)
{
	static char buffer[RD_BUFFER_SZ];
	static size_t j, len;
	size_t z;
	ssize_t q = 0, s = 0;
	char *pt = NULL, *new_pt = NULL, *c;

	pt = *ptr;
	if (pt && length)
	{
		s = *length;
	}

	if (j == len)
	{
		j = len = 0;
	}

	q = rd_buffer(details, buffer, &len);
	if (q == -1 || (q == 0 && len == 0))
	{
		return -1;
	}

	c = _strchr(buffer + j, '\n');
	z = c ? 1 + (size_t)(c - buffer) : len;
	new_pt = _realloc(pt, s, s ? s + z : z + 1);
	if (new_pt == NULL)
	{
		if (pt)
		{
			free(pt);
		}
		return (-1);
	}

	if (s)
	{
		_strncat(new_pt, buf + j, z - j);
	}
	else
	{
		_strncpy(new_pt, buf + j, z - j + 1);
	}

	s += z - j;
	j = z;
	pt = new_pt;

	if (length)
	{
		*length = s;
	}
	*ptr = pt;

	return (s);
}




/**
 * handleCtrlC - stops ctrl-C
 * @sign_id: the signal id
 * Return: void
 */


void handleCtrlC(__attribute__((unused)) int sign_id)
{
	char newline = '\n';
	char prompt[] = "$ ";

	write(STDOUT_FILENO, &newline, 1);
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
	write(STDOUT_FILENO, &newline, 1);
	fflush(stdout);
}
