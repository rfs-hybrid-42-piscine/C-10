/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tail.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 02:29:41 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 16:40:55 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TAIL_H
# define FT_TAIL_H

# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

/**
 * @file ft_tail.h
 * @brief Header file for the ft_tail project.
 * @details Contains system includes and custom utility prototypes.
 */

void	print_tail_error(char *file, char *program, bool invalid_bytes);
void	print_header(char *file, int mode);
void	print_buffer(char *buf, int total_bytes, int len);
int		ft_atoi(char *str);

#endif
