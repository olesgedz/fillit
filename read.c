/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 03:56:16 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/17 05:41:03 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size)
	{
		ft_memdel((void **)&(map->content[i]));
		i++;
	}
	ft_memdel((void **)&(map->content));
}

/*
* Moves figure to (0,0) point
*/
char		**ft_normfigure(char **dst, t_etris *figure)
{
	int j;
	int k;

	j = figure->y;
	while (j < figure->height + figure->y)
	{
		k = figure->x;
		while (k < figure->width + figure->x)
		{
			if (figure->content[j][k] == '#')
			{
				figure->content[j][k] = '.';
				figure->content[j - figure->y][k - figure->x] = '#';
			}
			k++;
		}
		j++;
	}
	figure->y = 0;
	figure->x = 0;
	return (dst);
}

void		ft_free_everything(t_map *map, t_etris **figures)
{
	int i;

	ft_free_map(map);
	free(map);
	i = 0;
	while (i < 26)
	{
		if (figures[i]->content != NULL)
			ft_2darrayclean(&(figures[i]->content));
		ft_memdel((void**)&figures[i]);
		i++;
	}
		free(figures);
		figures = NULL;
}

static int		ft_readFigures(t_etris **figures,	int fd, int *number)
{
	int i;
	int flag;
	char *line;

	line = "";
	flag = 1;
	i = 0;
	while (i < 5)
	{
		flag = get_next_line(fd, &line);
		if (i < 4)
		{
			figures[*number]->content[i] = ft_strdup(line);
			if (ft_strlen(figures[*number]->content[i]) != 4)
					ft_error();
			free(line);
		}
		else
		{
			if (ft_strlen(line) != 0)
				ft_error();
		}
		i++;
	}
	return(flag);
}


int		ft_readmap(t_etris **figures, int fd)
{
	int flag;
	unsigned char c;
	int number;

	flag = 1;
	c = 'A';
	number = 0;

	while (flag)
	{
		if (number >= 26)
			ft_error();
		figures[number]->id = c++;
		figures[number]->content = (char **)malloc(sizeof(char *) * 5);
		flag = ft_readFigures(figures, fd, &number);
		figures[number]->content[4] = NULL;
		number++;
	}
	close(fd);
	return (number);
}
