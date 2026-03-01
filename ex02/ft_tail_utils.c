/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:57:11 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 15:56:57 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tail.h"

/**
 * @fn static void ft_putstr(int fd, char *str)
 * @brief Safely prints a string to a specific file descriptor.
 * @details Iterates through the string and writes each character to the given
 * file descriptor, skipping execution if the string pointer is NULL.
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
 * @fn void print_tail_error(char *arg, char *program, bool invalid_bytes)
 * @brief Centralized error handler for the tail program.
 * @details Parses specific invalid byte string errors, or retrieves standard
 * global errno strings and prints them securely to standard error.
 * @param arg The argument or file name that caused the error.
 * @param program The name of the executed program (argv[0]).
 * @param invalid_bytes Boolean flag to indicate if the error is due to an 
 * invalid byte count formatting.
 */
void	print_tail_error(char *arg, char *program, bool invalid_bytes)
{
	if (invalid_bytes)
	{
		ft_putstr(2, basename(program));
		ft_putstr(2, ": invalid number of bytes: ‘");
		ft_putstr(2, arg);
		ft_putstr(2, "’\n");
		return ;
	}
	ft_putstr(2, basename(program));
	ft_putstr(2, ": ");
	ft_putstr(2, arg);
	ft_putstr(2, ": ");
	ft_putstr(2, strerror(errno));
	ft_putstr(2, "\n");
}

/**
 * @fn void print_header(char *file, int mode)
 * @brief Prints the formatting headers required when reading multiple files.
 * @details Outputs "==> filename <==" before a file's content, adjusting
 * vertical spacing based on the mode (e.g., separating files with newlines).
 * @param file The name of the file being printed.
 * @param mode The display mode (0 for single file, 1 for first of multiple, 
 * 2 for subsequent files).
 */
void	print_header(char *file, int mode)
{
	if (mode == 0)
		return ;
	if (mode == 2)
		write(1, "\n", 1);
	write(1, "==> ", 4);
	if (file[0] == '-' && file[1] == '\0')
		ft_putstr(1, "standard input");
	else
		ft_putstr(1, file);
	write(1, " <==\n", 5);
}

/**
 * @fn void print_buffer(char *buf, int total_bytes, int len)
 * @brief Prints the circular buffer chronologically.
 * @details Uses modulo arithmetic to find the oldest data point and prints
 * the buffer in two sequential writes to ensure correct character ordering.
 * @param buf The circular buffer containing the read data.
 * @param total_bytes The total number of bytes read from the file.
 * @param len The maximum number of bytes to print (the -c argument).
 */
void	print_buffer(char *buf, int total_bytes, int len)
{
	int	start;

	if (total_bytes <= len)
		write(1, buf, total_bytes);
	else
	{
		start = total_bytes % len;
		write(1, &buf[start], len - start);
		write(1, buf, start);
	}
}

/**
 * @fn int ft_atoi(char *str)
 * @brief Strict string-to-integer conversion.
 * @details Specifically tailored for tail. It rejects non-numeric characters
 * immediately, returning -1 to trigger standard command-line failure.
 * @param str The string representing the number of bytes.
 * @return The parsed integer, or -1 if the string is invalid.
 */
int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	if (*str)
		return (-1);
	return (res);
}
