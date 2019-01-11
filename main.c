/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/11 21:26:12 by jblack-b         ###   ########.fr       */
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
	char				**content;
	int 					valid;
	t_etris				*last;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
};

typedef struct s_map
{
	char **content;
	int size;
} t_map;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void		ft_count_nieghbors(int j, int k, int *count, char **temp)
{
	if (temp[j][k] == '#')
	{
		*count += 1;
		if (k - 1 >= 0 && temp[j][k - 1] == '#')
			*count += 1;
		if (k + 1 <= 3 && temp[j][k + 1] == '#')
			*count += 1;
		if (j - 1 >= 0 && temp[j - 1][k] == '#')
			*count += 1;
		if (j + 1 <= 3 && temp[j + 1][k] == '#')
			*count += 1;
	}
}

int		ft_checkwidth(char **figure, int j, int *map)
{
	if (ft_strlen(figure[j]) != 4)
		*map = 0;
	return (*map);
}

int		ft_validate(t_etris *figure)
{
	int		j;
	int		k;
	int		count;
	int		map;

	map = 1;
	j = 0;
	count = 0;
	while (j < 4)
	{
		k = 0;
		ft_checkwidth(figure->content, j, &map);
		while (k < 4)
		{
			if ((figure->content)[j][k] != '#' && (figure->content)[j][k] != '.')
				map = 0;
			ft_count_nieghbors(j, k++, &count, figure->content);
		}
		j++;
	}
	if ((count == 10 || count == 12) && map == 1)
		figure->valid = 1;
	else

		figure->valid = 0;
	return (figure->valid);
}
int		ft_getsizeY(t_etris *figure)
{
	int j;
	int start;
	int end;
	int temp;

	j = 0;
	start = -1;
	while (j < 4)
	{
		if (ft_strchr(figure->content[j], '#'))
		{
			if (start == -1)
				start = j;
			end = j;
		}
		j++;
	}
	figure->height = end - start + 1;
	figure->y = start;
	return (end - start + 1);
}


int		ft_getsizeX(t_etris *figure)
{
	int j;
	int k;
	int start;
	int end;

	start = 5;
	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (figure->content[j][k] == '#')
			{
				if (start > k)
					start = k;
				if (end < k)
					end = k;
			}
			k++;
		}
		j++;
	}
	figure->width = end - start + 1;
	figure->x = start;
	return (end - start + 1);
}

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
				figure->content[j - figure->y][k - figure->x] = \
				figure->content[j][k];
				figure->content[j][k] = '.';
			}
			k++;
		}
		j++;
	}
	return (dst);
}

int		ft_cleanfigure(t_map *map, t_etris *figure)
{
	int k;
	int j;

	j = 0;
	while (j < map->size)
	{
		k = 0;
		while (k < map->size)
		{
			if (map->content[j][k] == figure->id)
				map->content[j][k] = '.';
			k++;
		}
		j++;
	}
	return (0);
}

int		ft_putfigure(t_map *map, t_etris *figure, t_point *p)
{
	int j;
	int k;

	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (figure->content[j][k] == '#')
			{
				if ((j + p->y >= map->size)  || (k + p->x  >= map->size) || map->content[j + p->y][k + p->x] != '.')
				{
					ft_cleanfigure(map, figure);
					return (0);
				}
				else
					map->content[j + p->y][k + p->x] = figure->id;
			}
			k++;
		}
		j++;
	}
	return (0);
}

char**		ft_2darraynew(size_t y, size_t x, char c)
{
	char** new;
	size_t j;
	size_t k;

	if (!(new = (char **)(malloc(sizeof(char *) * y + 1))))
		return (NULL);
	new[y] = NULL;

	j = 0;
	while (j < y)
	{
		if (!(new[j]= (char *)(malloc(sizeof(char ) * x + 1))))
			return (NULL);
		new[j][x] = '\0';
		k = 0;
		while (k < x)
		{
			new[j][k] = c;
			k++;
		}
		j++;
	}
	return (new);
}

t_point		*point_new(int x, int y)
{
	t_point		*point;

	point = ft_memalloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
}




int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;

	char **matrix;
	int i;
	t_etris **figures;
	uint64_t temp;
	int j;
	char *line;

	j = 0;
	figures =malloc(sizeof(t_etris *) * 16);
	while (j < 16)
	{
		figures[j] = malloc(sizeof(t_etris));
		figures[j]->content = malloc(sizeof(char *) * 5);
		figures[j++]->content[5] = NULL;
	}
	i = 0;
	if (argc < 2)
	{
		ft_putstr("ERROR");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	j = 0;  // number of tettrinos
	int flag = 1; //._.
	unsigned char c = 'A';
	while (flag)
	{
		figures[j]->id = c++;
		while ((flag = get_next_line(fd, &line)) && i < 4)
		{
			figures[j]->content[i] = ft_strdup(line);
			i++;
			free(line);
		}
		figures[j]->content[i] = NULL;
		i = 0;
		j++;
	 }
	i = 0;
	while (i < j)
	{
		ft_validate(figures[i]);
		ft_getsizeY(figures[i]);
		ft_getsizeX(figures[i]);
		ft_normfigure(figures[i]->content, figures[i]);
		//ft_printmap(figures[i]->value);
		i++;
	}
	t_map *map = malloc(sizeof(t_map *));
	map->size = 5;
	map->content = ft_2darraynew(map->size, map->size, '.');
	ft_putfigure(map, figures[0], point_new(0 ,0));
//	ft_putfigure(map, figures[1], point_new(0,0));
	ft_printmap(map->content);
	return (0);
}
