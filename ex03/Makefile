# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 13:12:27 by maaugust          #+#    #+#              #
#    Updated: 2026/03/01 15:40:09 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME        = ft_hexdump

# ============================== COMPILER FLAGS ============================== #
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I.
RM          = rm -f

# =============================== SOURCE FILES =============================== #
SRC         = ft_hexdump.c	\
              ft_hexdump_utils.c \
			  ft_hexdump_print.c
OBJ         = $(SRC:.c=.o)

# ============================ COMPILATION RULES ============================= #
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# ============================== CLEAN TARGETS =============================== #
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
