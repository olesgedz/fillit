/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 03:56:16 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/17 15:32:11 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>

void			ft_free_map(t_map *map)
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
**Moves figure to (0,0) point
*/

char			**ft_normfigure(char **dst, t_etris *figure)
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

void			ft_free_everything(t_map *map, t_etris **figures)
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

int				ft_readfigures(t_etris **figures, int fd, int *number)
{
	int			i;
	int			flag;
	char		*line;
	char		*end;

	end = NULL;
	line = "";
	flag = 1;
	i = 0;
	while (i < 5)
	{
		if (i < 4)
		{
			flag = get_next_line(fd, &line);
			figures[*number]->content[i] = ft_strdup(line);
			if (ft_strlen(figures[*number]->content[i]) != 4)
				ft_error();
			free(line);
		}
		else
			ft_check_end(&flag, end, fd);
		i++;
	}
	return (flag);
}

int				ft_readmap(t_etris **figures, int fd)
{
	int				flag;
	unsigned char	c;
	int				number;

	flag = 1;
	c = 'A';
	number = 0;
	while (flag)
	{
		if (number >= 26)
			ft_error();
		figures[number]->id = c++;
		if (!(figures[number]->content = (char **)malloc(sizeof(char *) * 5)))
			ft_error();
		flag = ft_readfigures(figures, fd, &number);
		figures[number]->content[4] = NULL;
		number++;
	}
	close(fd);
	return (number);
}
