/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/03 21:03:27 by jblack-b         ###   ########.fr       */
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
	char				**value;
	int 					valid;
	t_etris				*last;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
};

int		ft_validate(t_etris *figure)
{
	char **temp;
	int j;
	int k;

	j = 0;
	k = 0;
	temp = figure->value;
	while (j < 4)
	{
		if (ft_strchr(figure->value[j], '#'))
		{
			//ft_putstr("\n");
			//ft_putstr(figure->value[j]);
			ft_putnbr(j);
			ft_putstr("\n");
		}
		j++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;

	char **matrix;
	int i;
	t_etris *figures[4];
	uint64_t temp;
	int j;
	char *line;

	j = 0;
	while (j < 4)
	{
		figures[j] = malloc(sizeof(t_etris));
		figures[j]->value = malloc(sizeof(char *) * 5);
		figures[j++]->value[5] = NULL;
	}
	matrix = (char **)(malloc(sizeof(char *) * 5));
	matrix[4] = NULL;
	i = 0;
	if (argc < 2)
	{
		ft_putstr("ERROR");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	j = 0;
	while (j < 4)
	{
		while (get_next_line(fd, &line) && i < 4)
		{
			figures[j]->value[i] = ft_strdup(line);
			//ft_putstr(figures[j]->value[i]);
			i++;
			free(line);
		}
		i = 0;
		j++;
	}
	i = 0;
	while (i < 4)
	{
		ft_printmap(figures[i]->value);
		ft_validate(figures[i]);
		i++;
	}
	return (0);
}
