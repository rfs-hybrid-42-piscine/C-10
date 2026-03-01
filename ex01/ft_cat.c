/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:40:27 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 15:57:37 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @fn static void ft_putstr(int fd, char *str)
 * @brief Prints a string to a dynamically specified file descriptor.
 * @details Reusable helper function to print error messages directly to
 * standard error (fd 2), bypassing standard output.
 * @param fd The file descriptor to write to.
 * @param str The null-terminated string to print.
 */
static void	ft_putstr(int fd, char *str)
{
	if (str)
		while (*str)
			write(fd, str++, 1);
}

/**
 * @fn static void print_cat_error(char *file, char *program)
 * @brief Formats and prints system errors to match the standard cat utility.
 * @details Extracts the executable name using basename, and translates the
 * current global errno into a human-readable string using strerror.
 * @param file The name of the file that caused the error.
 * @param program The name of the executed program (argv[0]).
 */
static void	print_cat_error(char *file, char *program)
{
	ft_putstr(2, basename(program));
	ft_putstr(2, ": ");
	ft_putstr(2, file);
	ft_putstr(2, ": ");
	ft_putstr(2, strerror(errno));
	ft_putstr(2, "\n");
}

/**
 * @fn static int ft_display_file(int fd, char *file, char *program)
 * @brief Reads a file descriptor and writes it to standard output.
 * @details Uses a 28KB stack buffer to comply with the subject's memory limit.
 * Checks if read() returns -1 to safely trigger the errno handler.
 * @param fd The file descriptor to read from.
 * @param file The name of the file being read.
 * @param program The name of the executed program.
 * @return 0 on success, 1 on read failure.
 */
static int	ft_display_file(int fd, char *file, char *program)
{
	char	buf[28672];
	ssize_t	bytes_read;
	size_t	nbytes;

	nbytes = sizeof(buf);
	bytes_read = read(fd, buf, nbytes);
	while (bytes_read > 0)
	{
		write(1, buf, bytes_read);
		bytes_read = read(fd, buf, nbytes);
	}
	if (bytes_read == -1)
	{
		print_cat_error(file, program);
		return (1);
	}
	return (0);
}

/**
 * @fn static int ft_cat(char *file, char *program)
 * @brief Manages the file descriptor pipeline for a single target.
 * @details Dynamically assigns fd 0 if the target is standard input ("-"). 
 * Otherwise, attempts to open the file. Ensures the fd is closed after reading.
 * @param file The target file or "-" for stdin.
 * @param program The name of the executed program.
 * @return 0 on success, 1 on open/read failure.
 */
static int	ft_cat(char *file, char *program)
{
	int	fd;
	int	status;

	if (file[0] == '-' && file[1] == '\0')
		fd = 0;
	else
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			print_cat_error(file, program);
			return (1);
		}
	}
	status = ft_display_file(fd, file, program);
	if (fd != 0)
		close(fd);
	return (status);
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point for the ft_cat utility.
 * @details Defaults to reading from standard input if no arguments are passed.
 * Otherwise, iterates through all arguments sequentially, tracking and
 * returning an exit status of 1 if any file fails to process.
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return 0 on success, 1 on error.
 */
int	main(int argc, char **argv)
{
	int	status;
	int	i;

	if (argc < 2)
		return (ft_cat("-", argv[0]));
	status = 0;
	i = 0;
	while (++i < argc)
		if (ft_cat(argv[i], argv[0]) != 0)
			status = 1;
	return (status);
}
