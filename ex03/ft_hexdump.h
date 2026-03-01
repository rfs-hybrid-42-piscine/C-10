/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:17:08 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 15:54:27 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEXDUMP_H
# define FT_HEXDUMP_H

# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

/**
 * @struct s_hex
 * @brief State machine structure for tracking hexdump parsing.
 * @param buf The current 16-byte chunk being parsed.
 * @param prev The previous 16-byte chunk, used to check for duplicates (*).
 * @param buf_len The current number of bytes loaded into the buffer.
 * @param offset The global byte offset tracking the file's progress.
 * @param is_star Boolean flag preventing multiple asterisks for identical
 * lines.
 * @param c_flag Boolean flag indicating if the -C canonical format is active.
 */
typedef struct s_hex
{
	char			buf[16];
	char			prev[16];
	int				buf_len;
	unsigned int	offset;
	bool			is_star;
	bool			c_flag;
}	t_hex;

int		ft_strcmp(char *s1, char *s2);
int		ft_memcmp(const void *s1, const void *s2, int n);
char	*ft_strncpy(char *dest, const char *src, int n);
void	print_hexdump_error(char *file, char *program);
void	print_offset(unsigned int offset, int len);
void	print_line(t_hex *state, int size);

#endif
