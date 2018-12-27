# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/28 01:17:41 by olesgedz          #+#    #+#              #
#    Updated: 2018/12/28 01:57:27 by olesgedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = main.c
OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS= -Wall -Wextra -Werror

LIBFT= ./libft/libft.a
LIBINC= -I ./libft

all: $(NAME)

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft

$(GNL):
	clang $(CFLAGS) -o ./get_next_line/get_next_line.c  -I ./get_next_line.h

$(NAME): libft $(OBJ)
	@$(CC) $(LIBFT) $(GNL) -o $(NAME) $(OBJ)

debug: libft $(OBJ)
	@$(CC) $(LIBLINK) -g $(SRC)

remlib:
	@rm -rf $(LIBFT)

remoblib:
	@make fclean -C ./libft/

clean: remoblib
	@rm -rf $(OBJ)

fclean: clean remlib
	@rm -rf $(NAME)

re: fclean all
