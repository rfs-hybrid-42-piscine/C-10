/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:03:42 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/26 18:42:25 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * @fn static void ft_display_file(int fd)
 * @brief Reads a file descriptor and writes its content to the standard output.
 * @details Uses a 4096-byte fixed-size buffer to read chunks of the file in a 
 * loop until the end of the file (EOF) is reached. This optimizes system calls 
 * while strictly avoiding dynamic memory allocation.
 * @param fd The file descriptor of the open file to be read.
 */
static void	ft_display_file(int fd)
{
	char	buf[4096];
	ssize_t	bytes_read;
	size_t	nbytes;

	nbytes = sizeof(buf);
	bytes_read = read(fd, buf, nbytes);
	while (bytes_read > 0)
	{
		write(1, buf, bytes_read);
		bytes_read = read(fd, buf, nbytes);
	}
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point for the ft_display_file program.
 * @details Validates the argument count, safely opens the requested file in
 * read-only mode, and manages system error strings by writing them explicitly
 * to the standard error output (file descriptor 2).
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return 0 on success, 1 on error.
 */
int	main(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		if (argc == 1)
			write(2, "File name missing.\n", 19);
		else
			write(2, "Too many arguments.\n", 20);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	ft_display_file(fd);
	close(fd);
	return (0);
}
