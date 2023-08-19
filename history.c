#include "shell.h"

/**
 * get_history - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history(t_info *details)
{
	char *buff, *file;

	file = get_env(details, "HOME=");
	if (!file)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(file) + _strlen(FILE_HISTORY) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, file);
	_strcat(buff, "/");
	_strcat(buff, FILE_HISTORY);
	return (buff);
}

/**
 * write_history - creates a file, or adds to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wr_hist(t_info *details)
{
	ssize_t fd;
	char *file_name;
	t_list *node;

	file_name = get_history(details);
	node = details->hist;

	if (!file_name)
		return (-1);

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	if (fd == -1)
		return (-1);

	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUFFER_FLUSH, fd);

	close(fd);

	return (1);
}


/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

int rd_hist(t_info *details)
{
	int j, end = 0, ln_cnt = 0;
	ssize_t fd, readlength, file_sz = 0;
	struct stat st;
	char *buff = NULL, *file_name = get_history(details);

	if (!file_name)
		return 0;
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		file_sz = st.st_size;
	if (file_sz < 2)
	{
		close(fd);
		return (0);
	}
	buff = malloc(sizeof(char) * (file_sz + 1));
	if (!buff)
	{
		close(fd);
		return (0);
	}
	readlength = read(fd, buff, file_sz);
	buff[fsize] = 0;
	if (readlength <= 0)
	{
		free(buff);
		close(fd);
		return (0);
	}
	close(fd);
	j = 0;
	while (j < file_sz)
	{
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			hist_build(info, buff + end, ln_cnt++);
			end = j + 1;
		}
		j++;
	}
	if (end != j)
	hist_build(info, buff + end, ln_cnt++);
	free(buff);
	details->hist_cnt = ln_cnt;
	for (; details->hist_cnt >= HIST_LIMIT; details->hist_cnt--)
	{
		rem_node_at_index(&(details->hist), 0);
	}
	hist_renum(details);
	return (details->hist_cnt);
}


/**
 * build_history - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @line_count: the history linecount, histcount
 *
 * Return: Always 0
 */

int hist_build(t_info *details, char *buff, int ln_cnt)
{
	t_list *node = NULL;

	if (details->hist)
		node = details->hist;
	insert_node_end(&node, buff, ln_cnt);

	if (!details->hist)
		details->hist = node;
	return (0);
}

/**
 * re_number_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

int hist_renum(t_info *details)
{
	int j;

	t_list *node = details->hist;
	
	for (j = 0; node; j++)
	{
		node->num = j;
		node = node->next;
	}

	details->hist_cnt = j;

	return (details->hist_cnt);
}
