/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:13:00 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/17 03:10:58 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "fillit.h"

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

t_point		*ft_point_new(int x, int y)
{
	t_point		*point;

	point = ft_memalloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
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
	j = -1;
	count = 0;
	while (++j < 4)
	{
		k = 0;
		ft_checkwidth(figure->content, j, &map);
		while (k < 4)
		{
			if ((figure->content)[j][k] != '#'
			&& (figure->content)[j][k] != '.')
				map = 0;
			ft_count_nieghbors(j, k++, &count, figure->content);
		}
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

	end = -1;
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
	figure->x = start;
	return (figure->width = end - start + 1);
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

void	ft_putfigure(t_etris *tetri, t_map *map, t_point *point, char c)
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

int		ft_checkplace(t_etris *tetri, t_map *map, int x, int y)
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

int		ft_solve(t_map *map, t_etris **figure)
{
	int x;
	int y;

	if ((*figure)->content == NULL)
		return (1);
	y = 0;
	while (y < map->size - (*figure)->height + 1)
	{
		x = 0;
		while (x < map->size - (*figure)->width + 2)
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

int		ft_minmap(int n)
{
	int size;

	size = 2;
	while (size * size < n)
		size++;
	return (size);
}

void		ft_error()
{
	ft_putstr("error\n");
	exit(1);
}

int		ft_readFigures(t_etris **figures,	int fd, int *number)
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
		figures[number]->id = c++;
		figures[number]->content = (char **)malloc(sizeof(char *) * 5);
		flag = ft_readFigures(figures, fd, &number);
		figures[number]->content[4] = NULL;
		number++;
	 }
	return (number);
}

int		ft_file_valid(t_etris **figures, int number)
{
	int i;

	i = 0;
	while (i < number)
	{
		if (!ft_validate(figures[i]))
		{
			ft_putstr("error\n");
			exit(1);
		}
		ft_getsizeY(figures[i]);
		ft_getsizeX(figures[i]);
		ft_normfigure(figures[i]->content, figures[i]);
		i++;
	}
	return (0);
}

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

t_map 	*ft_map_init(int n)
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	map->size = ft_minmap(n * 4);
	map->nfigures = n;
	return(map);
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

void		ft_figures_init(t_etris ***figures)
{
	int i;

	i = 0;
	*figures = malloc(sizeof(t_etris*) * 26);
	while (i < 26)
	{
		(*figures)[i] =  malloc(sizeof(t_etris));
		((*figures)[i])->content = NULL;
		i++;
	}
}
void		ft_mainloop(t_etris **figures, t_map *map)
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

int		main(int argc, char **argv)
{
	t_etris **figures;
	int nfigures;
	t_map *map;

	if (argc < 2)
	{
		ft_putstr("No input file\n");
		return (0);
	}
	ft_figures_init(&figures);
	nfigures = ft_readmap(figures, open(argv[1], O_RDONLY));
	ft_file_valid(figures, nfigures);
	map = ft_map_init(nfigures);
	ft_mainloop(figures, map);
	ft_printmap(map->content);
	ft_free_everything(map, figures);
	return (0);
}
