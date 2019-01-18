/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 04:07:12 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/19 02:11:05 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include "libft.h"

static void		ft_putfigure(t_etris *tetri, t_map *map, t_point *point, char c)
{
	int i;
	int j;

	i = 0;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->content[j][i] == '#')
				map->content[point->y + j][point->x + i] = c;
			j++;
		}
		i++;
	}
	ft_memdel((void **)&point);
}

/*
**Looks if that figure can fit at that point
**and uses ft_putfigure to write it down in map;
*/

static int		ft_checkplace(t_etris *tetri, t_map *map, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < tetri->width)
	{
		j = 0;
		while (j < tetri->height)
		{
			if (tetri->content[j][i] == '#'
			&& map->content[y + j][x + i] != '.')
				return (0);
			j++;
		}
		i++;
	}
	ft_putfigure(tetri, map, ft_point_new(x, y), tetri->id);
	return (1);
}

/*
**Just recursion moving by (x,y) and tring to fit
*/

static int		ft_solve(t_map *map, t_etris **figure)
{
	int x;
	int y;

	if ((*figure)->content == NULL)
		return (1);
	y = 0;
	while (y < map->size - (*figure)->height + 1)
	{
		x = 0;
		while (x < map->size - (*figure)->width + 1)
		{
			if (ft_checkplace(*figure, map, x, y))
			{
				if (ft_solve(map, figure + 1))
					return (1);
				ft_putfigure(*figure, map, ft_point_new(x, y), '.');
			}
			x++;
		}
		y++;
	}
	return (0);
}

void			ft_mainloop(t_etris **figures, t_map *map)
{
	while (1)
	{
		map->content = ft_2darraynew(map->size, map->size, '.');
		if (ft_solve(map, figures))
			break ;
		else
		{
			ft_free_map(map);
			map->size++;
		}
	}
}
