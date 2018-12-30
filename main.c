/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/30 02:12:15 by olesgedz         ###   ########.fr       */
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

int		ft_putbit(int j, int k, uint64_t *value)
{
	return (*value |= 1 << ((j * 8) + k));
}

int		ft_atob(t_etris *figure, char **matrix)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (j < 4)
	{
		while (k < 4)
		{
			if (matrix[j][k] == '#')
			{
				ft_putbit(j, k, &figure->value);
				//printf(" s d:%d, %d ", j, k);
			}
			k++;
		}
		k = 0;
		j++;
	}
	return (0);
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
	// //	figure->value <<= 1;
	// figure->value |= ~((unsigned int)0);
	// figure->value |= figure->value << 32;
	// //figure->value <<= 8;
	
	ft_atob(figure, matrix);
	ft_print_binary(figure->value);
	return (0);
}