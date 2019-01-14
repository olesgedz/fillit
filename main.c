/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:13:00 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/14 21:12:09 by olesgedz         ###   ########.fr       */
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
		// ft_printmap(dst);
		// ft_putchar('\n');
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
	int count = 0;
	j = 0;

	//ft_cleanfigure(map, figure);
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			  // ft_printmap(map->content);
			  // 	ft_putchar('\n');
			if (figure->content[j][k] == '#')
			{
				if (j + p->y >= map->size || k + p->x  >= map->size)
				{
					ft_cleanfigure(map, figure);
					return (0);
				}
				else
				{
					if (map->content[j + p->y][k + p->x] != '.')
					{
						ft_cleanfigure(map, figure);
						return (0);
					}
					else
					{
						count++;
						map->content[j + p->y][k + p->x] = figure->id;
						if (count >= 4)
							return (1);
					}
				}
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

int		ft_solve(t_map *map, t_etris **figure)
{
	int x = 0;
	int y = 0;
	//printf("%pHERE\n", (*figure)->content);
	if ((*figure)->content == NULL)
		return (1);
	y = 0;
	while (y < map->size - (*figure)->height + 1)
	{
		x = 0;
		while (x < map->size - (*figure)->width + 2)
		{
			if (ft_putfigure(map, *figure, point_new(x, y)))
			{
				//ft_printmap(map->content);
				if (ft_solve(map, figure + 1))
					return (1);
					ft_cleanfigure(map, *figure);
			}
			//printf("x:%d, y:%d\n", x, y);
			x++;
		}
		y++;
	}
	return (0);
}

int		ft_test(t_map *map, t_etris **figure)
{
	figure+=0;
	ft_printmap((*figure)->content);
	return (0);
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
	figures =malloc(sizeof(t_etris *) * 26);
	while (number < 26)
	{
		figures[number] = malloc(sizeof(t_etris));
		figures[number]->content= NULL;
		number++;
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
		figures[number]->content = (char **)malloc(sizeof(char *) * 5);
		while (i < 5)
		{
			flag = get_next_line(fd, &line);
			if (i < 4)
			{
				figures[number]->content[i] = ft_strdup(line);
				if (ft_strlen(figures[number]->content[i]) != 4)
				{
					ft_putstr("error\n");
					exit(1);
				}
				free(line);
			}
			else
			{
				if (!(ft_strlen(line) == 0))
				{
					ft_putstr("error\n");
					exit(1);
				}
				// i++;
			}
			i++;
		}
		figures[number]->content[4] = NULL;
		i = 0;
		number++;
	 }
	// figures[number -1]->content = NULL;
	i = 0;
	//printf("ll%d\n", number);
	//ft_printmap(figures[1]->content);
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
		//printf("x:%d, y:%d w:%d h:%d\n", figures[i]->x, figures[i]->y, figures[i]->width, figures[i]->height);
	//ft_printmap(figures[i]->content);
		i++;
	}

	t_map *map = malloc(sizeof(t_map));
	map->size = 2;
	while (1)
	{
			map->content = ft_2darraynew(map->size, map->size, '.');
			if (ft_solve(map, figures))
				break ;
			else
				map->size++;
		//ft_printmap(map->content);
	}
	ft_printmap(map->content);

	return (0);
}
