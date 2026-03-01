# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 13:12:27 by maaugust          #+#    #+#              #
#    Updated: 2026/02/26 14:08:01 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME        = ft_display_file

# ============================== COMPILER FLAGS ============================== #
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# =============================== SOURCE FILES =============================== #
SRC         = ft_display_file.c
OBJ         = $(SRC:.c=.o)

# ============================ COMPILATION RULES ============================= #
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
