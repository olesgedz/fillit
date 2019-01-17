# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/29 18:10:26 by jblack-b          #+#    #+#              #
#    Updated: 2019/01/17 06:01:35 by olesgedz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fillit

SRC = main.c validation.c read.c solve.c init.c
OBJ = $(SRC:.c=.o)

CC = clang

CFLAGS= -Wall -Wextra -Werror

LIBFT= ./libft/libft.a
LIBINC= -I ./libft/includes/

$(NAME): $(OBJ) $(LIBFT)
	$(CC)  $(LIBFT) $(OBJ) $(LIBINC) -o $(NAME) 	&& make clean -C ./libft

all: $(NAME)



$(OBJ): $(SRC)
	clang -c $(SRC) $(LIBINC)

libft: $(LIBFT)

$(LIBFT):
	make -C ./libft
coffee:
	echo "hello"

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
