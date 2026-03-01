/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 21:05:47 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 15:57:08 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

/**
 * @fn static long read_file(char *buf, int fd, int len)
 * @brief Reads the file in chunks and populates a dynamic circular buffer.
 * @details Continuously reads into a 4096-byte temporary buffer and copies
 * the requested tail length into the circular buffer, tracking total bytes read.
 * @param buf The circular buffer to store the final bytes.
 * @param fd The file descriptor to read from.
 * @param len The target number of bytes to keep.
 * @return The total number of bytes read, or -1 on error.
 */
static long	read_file(char *buf, int fd, int len)
{
	char	tmp[4096];
	long	total_bytes;
	size_t	nbytes;
	ssize_t	bytes_read;
	ssize_t	i;

	total_bytes = 0;
	nbytes = sizeof(tmp);
	bytes_read = read(fd, tmp, nbytes);
	while (bytes_read > 0)
	{
		i = -1;
		while (++i < bytes_read)
		{
			if (len > 0)
				buf[total_bytes % len] = tmp[i];
			total_bytes++;
		}
		bytes_read = read(fd, tmp, nbytes);
	}
	if (fd != 0)
		close(fd);
	if (bytes_read == -1)
		return (-1);
	return (total_bytes);
}

/**
 * @fn static int ft_tail(char *file, char *program, int len, int mode)
 * @brief Orchestrates file descriptor management and memory cleanup.
 * @details Opens the file (or uses stdin), allocates the circular buffer,
 * triggers the read process, and manages printing and freeing memory safely.
 * @param file The file name to read, or "-" for standard input.
 * @param program The program name for error reporting.
 * @param len The number of bytes to read from the end of the file.
 * @param mode The formatting mode for headers.
 * @return 0 on success, 1 on any failure (open, malloc, or read error).
 */
static int	ft_tail(char *file, char *program, int len, int mode)
{
	char	*buf;
	int		fd;
	long	total_bytes;

	fd = 0;
	if (!(file[0] == '-' && file[1] == '\0'))
		fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_tail_error(file, program, false);
		return (1);
	}
	print_header(file, mode);
	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (1);
	total_bytes = read_file(buf, fd, len);
	if (total_bytes < 0)
	{
		print_tail_error(file, program, false);
		return (free(buf), 1);
	}
	if (len > 0)
		print_buffer(buf, total_bytes, len);
	return (free(buf), 0);
}

/**
 * @fn static int execute_tail(int argc, char **argv, int index, int len)
 * @brief Iterates sequentially through multiple target files.
 * @details Determines the correct header mode and calls ft_tail for each
 * provided file argument, tracking the overall exit status.
 * @param argc The total argument count.
 * @param argv The argument vector array.
 * @param index The starting index of the file arguments.
 * @param len The number of bytes to read from the end of each file.
 * @return 0 on total success, 1 if any file encounters an error.
 */
static int	execute_tail(int argc, char **argv, int index, int len)
{
	int	mode;
	int	status;

	status = 0;
	if (argc - index == 0)
		return (ft_tail("-", argv[0], len, 0));
	mode = 0;
	if (argc - index > 1)
		mode = 1;
	while (index < argc)
	{
		if (ft_tail(argv[index], argv[0], len, mode) != 0)
			status = 1;
		index++;
		if (mode == 1)
			mode = 2;
	}
	return (status);
}

/**
 * @fn static int parse_args(int argc, char **argv, int *len)
 * @brief Identifies the layout of the -c flag and extracts its numeric value.
 * @details Supports both attached flags (e.g., -c50) and detached flags
 * (e.g., -c 50) to extract the integer length.
 * @param argc The argument count.
 * @param argv The argument vector array.
 * @param len A pointer to store the extracted byte length.
 * @return The index of the first file argument, or -1 on parse failure.
 */
static int	parse_args(int argc, char **argv, int *len)
{
	if (argv[1][2])
	{
		*len = ft_atoi(&argv[1][2]);
		return (2);
	}
	else if (argc > 2)
	{
		*len = ft_atoi(argv[2]);
		return (3);
	}
	return (-1);
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point that validates the required flag syntax and limits.
 * @details Checks for the -c flag, initiates argument parsing, handles missing
 * parameter edge-cases to prevent segfaults, and triggers execution.
 * @param argc The total argument count.
 * @param argv The argument vector array.
 * @return 0 on success, 1 on formatting failure or system error.
 */
int	main(int argc, char **argv)
{
	int	len;
	int	index;

	if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'c')
	{
		index = parse_args(argc, argv, &len);
		if (index == -1 || len < 0)
		{
			if (argv[1][2])
				print_tail_error(&argv[1][2], argv[0], true);
			else if (argc > 2)
				print_tail_error(argv[2], argv[0], true);
			else
				print_tail_error("", argv[0], true);
			return (1);
		}
		return (execute_tail(argc, argv, index, len));
	}
	return (0);
}
