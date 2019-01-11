/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numberbl <numberbl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by numberbl          #+#    #+#             */
/*   Updated: 2019/01/11 22:13:19 by jblack-b         ###   ########.fr       */
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

void		ft_count_nieghbors(int number, int k, int *count, char **temp)
{
	if (temp[number][k] == '#')
	{
		*count += 1;
		if (k - 1 >= 0 && temp[number][k - 1] == '#')
			*count += 1;
		if (k + 1 <= 3 && temp[number][k + 1] == '#')
			*count += 1;
		if (number - 1 >= 0 && temp[number - 1][k] == '#')
			*count += 1;
		if (number + 1 <= 3 && temp[number + 1][k] == '#')
			*count += 1;
	}
}

int		ft_checkwidth(char **figure, int number, int *map)
{
	if (ft_strlen(figure[number]) != 4)
		*map = 0;
	return (*map);
}

int		ft_validate(t_etris *figure)
{
	int		number;
	int		k;
	int		count;
	int		map;

	map = 1;
	number = 0;
	count = 0;
	while (number < 4)
	{
		k = 0;
		ft_checkwidth(figure->content, number, &map);
		while (k < 4)
		{
			if ((figure->content)[number][k] != '#' && (figure->content)[number][k] != '.')
				map = 0;
			ft_count_nieghbors(number, k++, &count, figure->content);
		}
		number++;
	}
	if ((count == 10 || count == 12) && map == 1)
		figure->valid = 1;
	else

		figure->valid = 0;
	return (figure->valid);
}
int		ft_getsizeY(t_etris *figure)
{
	int number;
	int start;
	int end;
	int temp;

	number = 0;
	start = -1;
	while (number < 4)
	{
		if (ft_strchr(figure->content[number], '#'))
		{
			if (start == -1)
				start = number;
			end = number;
		}
		number++;
	}
	figure->height = end - start + 1;
	figure->y = start;
	return (end - start + 1);
}


int		ft_getsizeX(t_etris *figure)
{
	int number;
	int k;
	int start;
	int end;

	start = 5;
	number = 0;
	while (number < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (figure->content[number][k] == '#')
			{
				if (start > k)
					start = k;
				if (end < k)
					end = k;
			}
			k++;
		}
		number++;
	}
	figure->width = end - start + 1;
	figure->x = start;
	return (end - start + 1);
}

char		**ft_normfigure(char **dst, t_etris *figure)
{
	int number;
	int k;
	number = figure->y;
	while (number < figure->height + figure->y)
	{
		k = figure->x;
		while (k < figure->width + figure->x)
		{
			if (figure->content[number][k] == '#')
			{
				figure->content[number - figure->y][k - figure->x] = \
				figure->content[number][k];
				figure->content[number][k] = '.';
			}
			k++;
		}
		number++;
	}
	return (dst);
}

int		ft_cleanfigure(t_map *map, t_etris *figure)
{
	int k;
	int number;

	number = 0;
	while (number < map->size)
	{
		k = 0;
		while (k < map->size)
		{
			if (map->content[number][k] == figure->id)
				map->content[number][k] = '.';
			k++;
		}
		number++;
	}
	return (0);
}

int		ft_putfigure(t_map *map, t_etris *figure, t_point *p)
{
	int number;
	int k;

	number = 0;
	while (number < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (figure->content[number][k] == '#')
			{
				if ((number + p->y >= map->size)  || (k + p->x  >= map->size) || map->content[number + p->y][k + p->x] != '.')
				{
					ft_cleanfigure(map, figure);
					return (0);
				}
				else
					map->content[number + p->y][k + p->x] = figure->id;
			}
			k++;
		}
		number++;
	}
	return (0);
}

char**		ft_2darraynew(size_t y, size_t x, char c)
{
	char** new;
	size_t number;
	size_t k;

	if (!(new = (char **)(malloc(sizeof(char *) * y + 1))))
		return (NULL);
	new[y] = NULL;

	number = 0;
	while (number < y)
	{
		if (!(new[number]= (char *)(malloc(sizeof(char ) * x + 1))))
			return (NULL);
		new[number][x] = '\0';
		k = 0;
		while (k < x)
		{
			new[number][k] = c;
			k++;
		}
		number++;
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
	int number;
	char *line;

	number= 0;
	figures =malloc(sizeof(t_etris *) * 16);
	while (number< 16)
	{
		figures[number] = malloc(sizeof(t_etris));
		figures[number]->content = malloc(sizeof(char *) * 5);
		figures[number++]->content[5] = NULL;
	}
	i = 0;
	if (argc < 2)
	{
		ft_putstr("ERROR");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	number = 0;  // number of tettrinos
	int flag = 1; //._.
	unsigned char c = 'A';
	while (flag)
	{
		figures[number]->id = c++;
		while ((flag = get_next_line(fd, &line)) && i < 4)
		{
			figures[number]->content[i] = ft_strdup(line);
			i++;
			free(line);
		}
		figures[number]->content[i] = NULL;
		i = 0;
		number++;
	 }
	i = 0;
	while (i < number)
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

	int j;
	int k;
	j= 0;
	i = 0;
	int x = 0;
	int y = 0;
	int solved = 0;
	//ft_putfigure(map, figures[i], point_new(x,y));
	while (!solved)
	{
		map->content = ft_2darraynew(map->size, map->size, '.');
		map->size++;
		while(i < number)
		{
			if (ft_putfigure(map, figures[i], point_new(x,y)))
				i++;
			else
			{
				x++;
				if (x > map->size)
				{
					y++;
					x = 0;
				}
				if (y > map->size)
					i--;
				if (i < 0)
					break;
			}
		}
	}
	ft_printmap(map->content);
	return (0);
}
