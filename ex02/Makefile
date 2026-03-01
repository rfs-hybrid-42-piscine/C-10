# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 13:12:27 by maaugust          #+#    #+#              #
#    Updated: 2026/02/28 16:47:01 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME        = ft_tail

# ============================== COMPILER FLAGS ============================== #
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I.
RM          = rm -f

# =============================== SOURCE FILES =============================== #
SRC         = ft_tail.c	\
              ft_tail_utils.c
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
