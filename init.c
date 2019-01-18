/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 04:11:27 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/19 01:55:37 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include "libft.h"

int					ft_checkwidth(char **figure, int j, int *map)
{
	if (ft_strlen(figure[j]) != 4)
		*map = 0;
	return (*map);
}

/*
**Calculate minimal map size
*/

static int			ft_minmap(int n)
{
	int size;

	size = 2;
	while (size * size < n)
		size++;
	return (size);
}

void				ft_error(void)
{
	ft_putstr("error\n");
	exit(1);
}

t_map				*ft_map_init(int n)
{
	t_map *map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		ft_error();
	map->size = ft_minmap(n * 4);
	return (map);
}

void				ft_figures_init(t_etris ***figures)
{
	int i;

	i = 0;
	if (!(*figures = malloc(sizeof(t_etris*) * 26)))
		ft_error();
	while (i < 26)
	{
		if (!((*figures)[i] = malloc(sizeof(t_etris))))
			ft_error();
		((*figures)[i])->content = NULL;
		i++;
	}
}
