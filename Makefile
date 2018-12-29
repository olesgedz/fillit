# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/29 18:10:26 by jblack-b          #+#    #+#              #
#    Updated: 2018/12/29 22:08:19 by jblack-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fillit

SRC = main.c
OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS= -Wall -Wextra -Werror

LIBFT= ./libft/libft.a
LIBINC= -I ./libft/includes/

all: $(NAME) $(LIBFT)

$(NAME): $(SRC)
	$(CC) -g $(LIBFT) $(SRC) $(LIBINC) -o $(NAME)

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft

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
