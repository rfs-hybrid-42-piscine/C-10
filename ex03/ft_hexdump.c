/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:16:38 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/01 16:27:09 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hexdump.h"

/**
 * @fn static void finalize_ft_hexdump(t_hex *state)
 * @brief Manages the trailing offset and final buffer data upon EOF.
 * @details Flushes the remaining data out and calculates the final ending
 * byte offset of the entire file parsing sequence.
 * @param state A pointer to the active formatting state machine.
 */
static void	finalize_ft_hexdump(t_hex *state)
{
	if (state->buf_len > 0)
	{
		print_line(state, state->buf_len);
		state->offset += state->buf_len;
	}
	if (state->offset > 0)
	{
		if (state->c_flag == 1)
			print_offset(state->offset, 8);
		else
			print_offset(state->offset, 7);
		write(1, "\n", 1);
	}
}

/**
 * @fn static void handle_full_buffer(t_hex *state)
 * @brief Processes exactly 16 bytes of data.
 * @details Validates identical lines to collapse them into asterisks (*),
 * triggers printing functions, and updates the global byte offset.
 * @param state A pointer to the active formatting state machine.
 */
static void	handle_full_buffer(t_hex *state)
{
	if (state->offset == 0 || ft_memcmp(state->buf, state->prev, 16) != 0)
	{
		print_line(state, 16);
		ft_strncpy(state->prev, state->buf, 16);
		state->is_star = 0;
	}
	else if (state->is_star == 0)
	{
		write(1, "*\n", 2);
		state->is_star = 1;
	}
	state->offset += 16;
	state->buf_len = 0;
}

/**
 * @fn static void process_file(int fd, t_hex *state)
 * @brief Sequentially feeds data into the state machine buffer.
 * @details Reads raw blocks from the file descriptor and transfers them
 * byte-by-byte into the state->buf array, triggering processing at 16 bytes.
 * @param fd The open file descriptor.
 * @param state A pointer to the active formatting state machine.
 */
static void	process_file(int fd, t_hex *state)
{
	char	tmp[4096];
	ssize_t	bytes_read;
	ssize_t	i;

	bytes_read = read(fd, tmp, sizeof(tmp));
	while (bytes_read > 0)
	{
		i = -1;
		while (++i < bytes_read)
		{
			state->buf[state->buf_len] = tmp[i];
			state->buf_len++;
			if (state->buf_len == 16)
				handle_full_buffer(state);
		}
		bytes_read = read(fd, tmp, sizeof(tmp));
	}
}

/**
 * @fn static int execute_ft_hexdump(int argc, char **argv, int index,
 * t_hex *state)
 * @brief Orchestrates file sequencing and error propagation.
 * @details Steps through argument index arrays, safely opens target files (or
 * defaults to stdin if empty), processes them, and traps global errors.
 * @param argc The total argument count.
 * @param argv The argument vector array.
 * @param index The active array location for file evaluation.
 * @param state A pointer to the active formatting state machine.
 * @return 0 on success, 1 on any file open/read failures.
 */
static int	execute_ft_hexdump(int argc, char **argv, int index, t_hex *state)
{
	int	fd;
	int	status;

	status = 0;
	if (index == argc)
		process_file(0, state);
	while (index < argc)
	{
		fd = open(argv[index], O_RDONLY);
		if (fd == -1)
		{
			print_hexdump_error(argv[0], argv[index]);
			status = 1;
		}
		else
		{
			process_file(fd, state);
			close(fd);
		}
		index++;
	}
	return (status);
}

/**
 * @fn int main(int argc, char **argv)
 * @brief Entry point initializing the state machine and flag parsing.
 * @details Pre-processes the arguments to isolate the -C canonical flag,
 * zeroes out the state machine, triggers the execution pipeline, and terminates
 * the buffers gracefully.
 * @param argc The total argument count.
 * @param argv The argument vector array.
 * @return 0 on success, 1 on system error.
 */
int	main(int argc, char **argv)
{
	t_hex	state;
	int		index;
	int		status;

	index = 1;
	if (argc > 1 && ft_strcmp(argv[1], "-C") == 0)
		++index;
	state.buf_len = 0;
	state.offset = 0;
	state.is_star = 0;
	state.c_flag = (index == 2);
	status = execute_ft_hexdump(argc, argv, index, &state);
	finalize_ft_hexdump(&state);
	return (status);
}
