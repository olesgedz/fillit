/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/08 22:33:53 by jblack-b         ###   ########.fr       */
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
		ft_checkwidth(figure->value, j, &map);
		while (k < 4)
		{
			if ((figure->value)[j][k] != '#' && (figure->value)[j][k] != '.')
				map = 0;
			ft_count_nieghbors(j, k++, &count, figure->value);
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
		if (ft_strchr(figure->value[j], '#'))
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
			if (figure->value[j][k] == '#')
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
			if (figure->value[j][k] == '#')
			{
				figure->value[j - figure->y][k - figure->x] = \
				figure->value[j][k];
				figure->value[j][k] = '.';
			}
			k++;
		}
		j++;
	}
	return (dst);
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

void		ft_cleanfigure(char **dst, t_etris *figure)
{
	int j;
	int k;
	j = 0;
	while (j < ft_strlen(*dst))
	{
		k = 0;
		while (k < ft_strlen(*dst))
		{
			if (dst[j][k] == figure->id)
			{
				dst[j][k] = '.';
			}
			k++;
		}
		j++;
	}
}

char		**ft_putfigure(char **dst, t_etris *figure, int x, int y)
{
	int j;
	int k;
	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (figure->value[j][k] == '#')
			{
				if ((j + y >= ft_strlen(*dst))  || (k + x  >= ft_strlen(*dst)) || dst[j + y][k + x] != '.')
				{
					ft_cleanfigure(dst, figure);
					return (NULL);
				}
				else
					dst[j + y][k + x] = figure->id;
			}
			k++;
		}
		j++;
	}
	return (dst);
}

char**		ft_solve(t_etris *figure, char **map, int x, int y)
{
	int j;
	int k;
	int map_s;
	int flag;

	flag = 0;
	//ft_printmap(figure->value);
	map_s = ft_strlen(*map);
	j = 0;
	while(j < map_s)
	{
		k = 0;
		while (k < map_s)
		{
			if (ft_putfigure(map, figure, k + x, j + y) != NULL)
				return (map);
			k++;
		}
		j++;
	}
			//	break ;
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;

	char **matrix;
	int i;
	t_etris *figures[16];
	uint64_t temp;
	int j;
	char *line;

	j = 0;
	while (j < 16)
	{
		figures[j] = malloc(sizeof(t_etris));
		figures[j]->value = malloc(sizeof(char *) * 5);
		figures[j++]->value[5] = NULL;
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
			figures[j]->value[i] = ft_strdup(line);
			i++;
			free(line);
		}
		figures[j]->value[i] = NULL;
		i = 0;
		j++;
	 }
	i = 0;
	while (i < j)
	{
		ft_validate(figures[i]);
		ft_getsizeY(figures[i]);
		ft_getsizeX(figures[i]);
		ft_normfigure(figures[i]->value, figures[i]);
		//ft_printmap(figures[i]->value);
		i++;
	}
	char **map;


	i = 0;
	int map_size = 2;
	int solved = 0;
	int x = 0;
	int y = 0;
	while (!solved)
	{
		map = ft_2darraynew(map_size, map_size, '.');
		map_size++;
		i = 0;
		while (i < j)
		{
			x = 0;
			y = 0;
			if (ft_solve(figures[i], map, x, y) == NULL)
			{
				//ft_printmap(map);
				x++;
				if (x > map_size - 1)
				{
					y++;
					x = 0;
					if (y > map_size - 1)
						continue ;
				}
				if (i > 0)
				{
					ft_cleanfigure(map, figures[i - 1]);
						ft_solve(figures[i - 1], map, x, y);
				}
				else
				{
					ft_cleanfigure(map, figures[i]);
						ft_solve(figures[i], map, x, y);
				}
				//ft_printmap(map);
				solved = 0;
				break ;
			}
			else
			{
				solved = 1;
			}
			i++;

		}
	}
	// map = ft_2darraynew(5, 5, '.');
	// while (i < 4)
	// {
	// 	ft_solve(figures[i], map);
	// 	i++;
	// }
	ft_printmap(map);
	return (0);
}
