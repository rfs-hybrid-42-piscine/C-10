/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:35:47 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 16:25:05 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

/**
 * @fn static void print_hex_default(char *buf, int size)
 * @brief Prints binary data in default hexdump 16-bit word format.
 * @details Reverses the byte order to natively support Little-Endian
 * architecture representations.
 * @param buf The buffer containing the binary chunk.
 * @param size The active size of the buffer.
 */
static void	print_hex_default(char *buf, int size)
{
	char			*hex;
	int				i;
	unsigned char	byte[2];

	hex = "0123456789abcdef";
	i = 0;
	while (i < size)
	{
		byte[0] = (unsigned char)buf[i];
		byte[1] = 0;
		if (i + 1 < size)
			byte[1] = (unsigned char)buf[i + 1];
		write(1, " ", 1);
		write(1, &hex[byte[1] / 16], 1);
		write(1, &hex[byte[1] % 16], 1);
		write(1, &hex[byte[0] / 16], 1);
		write(1, &hex[byte[0] % 16], 1);
		i += 2;
	}
}

/**
 * @fn static void print_ascii(char *buf, int size)
 * @brief Formats the ASCII representation column for the -C flag.
 * @details Replaces non-printable characters (outside 32 to 126) with dots.
 * @param buf The buffer containing the binary chunk.
 * @param size The active size of the buffer.
 */
static void	print_ascii(char *buf, int size)
{
	int	i;

	i = 0;
	write(1, " |", 2);
	while (i < size)
	{
		if (buf[i] >= ' ' && buf[i] <= '~')
			write(1, &buf[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "|\n", 2);
}

/**
 * @fn static void print_hex_bytes(char *buf, int size)
 * @brief Prints pure hexadecimal byte mapping for the -C flag.
 * @details Spaces out each individual byte natively, adding an extra space at
 * the halfway mark (index 7) to mimic standard hexdump formatting.
 * @param buf The buffer containing the binary chunk.
 * @param size The active size of the buffer.
 */
static void	print_hex_bytes(char *buf, int size)
{
	char			*hex;
	int				i;
	unsigned char	c;

	hex = "0123456789abcdef";
	i = 0;
	write(1, "  ", 2);
	while (i < 16)
	{
		if (i < size)
		{
			c = (unsigned char)buf[i];
			write(1, &hex[c / 16], 1);
			write(1, &hex[c % 16], 1);
		}
		else
			write(1, "  ", 2);
		write(1, " ", 1);
		if (i == 7)
			write(1, " ", 1);
		i++;
	}
}

/**
 * @fn void print_offset(unsigned int offset, int len)
 * @brief Calculates and prints the hexadecimal file offset dynamically.
 * @param offset The global byte offset tracking value.
 * @param len The exact padding size (7 for default, 8 for -C).
 */
void	print_offset(unsigned int offset, int len)
{
	char	str[8];
	char	*hex;
	int		i;

	hex = "0123456789abcdef";
	i = len - 1;
	while (i >= 0)
	{
		str[i] = hex[offset % 16];
		offset /= 16;
		i--;
	}
	write(1, str, len);
}

/**
 * @fn void print_line(t_hex *state, int size)
 * @brief Routes formatting based on the state machine's c_flag.
 * @param state A pointer to the active formatting state machine.
 * @param size The size of the current buffer.
 */
void	print_line(t_hex *state, int size)
{
	if (state->c_flag == 1)
	{
		print_offset(state->offset, 8);
		print_hex_bytes(state->buf, size);
		print_ascii(state->buf, size);
	}
	else
	{
		print_offset(state->offset, 7);
		print_hex_default(state->buf, size);
		write(1, "\n", 1);
	}
}
