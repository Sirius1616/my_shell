#include "shell.h"

/**
 * main - starting point
 * @ac: count of argument
 * @av: vector arg
 * Return: 1 on success, 0 on error
 */
int main(int ac, char **av)
{
	t_info details[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_err(av[0]);
				puts_err(": 0: No access ");
				puts_err(av[1]);
				putchar_err('\n');
				putchar_err(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		details->read_file_desc = fd;
	}
	fill_env_list(details);
	rd_hist(details);
	hash(details, av);
	return (EXIT_SUCCESS);
}
