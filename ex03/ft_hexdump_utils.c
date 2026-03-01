/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:17:02 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 15:58:06 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

/**
 * @fn int ft_strcmp(char *s1, char *s2)
 * @brief Standard string comparison tool.
 * @details Compares two strings character by character to detect specific
 * flags.
 * @param s1 The first string.
 * @param s2 The second string.
 * @return 0 if strings match, non-zero otherwise.
 */
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/**
 * @fn int ft_memcmp(const void *s1, const void *s2, int n)
 * @brief Compares binary memory blocks.
 * @details Used specifically to detect if the current 16-byte buffer exactly
 * matches the previous one to trigger the asterisk (*) logic.
 * @param s1 The first memory block.
 * @param s2 The second memory block.
 * @param n The number of bytes to compare.
 * @return 0 if blocks match perfectly, non-zero otherwise.
 */
int	ft_memcmp(const void *s1, const void *s2, int n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	int					i;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = -1;
	while (++i < n)
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	return (0);
}

/**
 * @fn char *ft_strncpy(char *dest, const char *src, int n)
 * @brief Copies up to n characters from src to dest.
 * @details Copies the buffer into the state->prev tracker, padding with null
 * bytes if the source is smaller than n.
 * @param dest The destination array.
 * @param src The source array.
 * @param n The maximum number of bytes to copy.
 * @return A pointer to the destination string.
 */
char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = -1;
	while (++i < n && src[i])
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

/**
 * @fn static int ft_strlen(char *str)
 * @brief Computes the length of a string.
 * @param str The string to evaluate.
 * @return The integer length of the string.
 */
static int	ft_strlen(char *str)
{
	int	len;

	len = -1;
	while (str[++len])
		;
	return (len);
}

/**
 * @fn void print_hexdump_error(char *file, char *program)
 * @brief Formats and prints system errors strictly for hexdump.
 * @details Extracts the executable name, fetches the errno description, and
 * prints them to standard error (fd 2).
 * @param file The file that caused the error.
 * @param program The name of the executing program (argv[0]).
 */
void	print_hexdump_error(char *file, char *program)
{
	char	*program_name;
	char	*error_msg;

	program_name = basename(program);
	error_msg = strerror(errno);
	write(2, program_name, ft_strlen(program_name));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}
