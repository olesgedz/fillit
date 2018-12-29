/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/29 21:02:11 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct s_etris	t_etris;

struct				s_etris
{
	uint64_t			value;
	t_etris				*last;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
};

void	ft_print_binary(uint64_t nbr)
{
	int i;
	int g;

	g = sizeof(uint64_t) * 8 - 1;
	i = 0;
	while (i <= g)
	{
		ft_putnbr(((nbr >> i) % 2));
		i++;
		if (i % 8 == 0)
			ft_putchar('\n');
	}
	//ft_putnbr(nbr);
	nbr /= 2 * i;
	//ft_putnbr(nbr);
	//nbr % 2 == 1 ? ft_putnbr(1) : ft_putnbr(0);
	ft_putstr("\n");
}

int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	*line;
	char **matrix;
	int i;
	t_etris *figure;

	figure = malloc(sizeof(t_etris));
	matrix = (char **)(malloc(sizeof(char *) * 5));
	matrix[4] = NULL;
	i = 0;
	if (argc < 2)
	{
		ft_putstr("ERROR");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) && i < 4)
	{
		matrix[i] = ft_strdup(line);
		i++;
		free(line);
	}
	ft_printmap(matrix);
	figure->value = 0;
	figure->value = 1;
	figure->value <<= 1;
	// //	figure->value <<= 1;
	// figure->value |= ~((unsigned int)0);
	// figure->value |= figure->value << 32;
	// //figure->value <<= 8;

	ft_print_binary(figure->value);
	return (0);
}
