/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:10:33 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/04 18:05:05 by jblack-b         ###   ########.fr       */
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
	int count;
	int map;

	map = 1;
	j = 0;
	k = 0;
	count = 0;
	temp = figure->value;
	while (j < 4)
	{
		while (k < 4)
		{
			if (temp[j][k] != '#' && temp[j][k] != '.')
				map = 0;
			if (temp[j][k] == '#')
			{
				count++;
				if (k - 1 >= 0 && temp[j][k - 1] == '#')
					count++;
				if (k + 1 <= 3 && temp[j][k + 1] == '#')
					count++;
				if (j - 1 >= 0 && temp[j - 1][k] == '#')
					count++;
				if (j + 1 <= 3 && temp[j + 1][k] == '#')
					count++;
			}
			k++;
		}
		k = 0;
		j++;
	}
	if ((count == 10 || count == 12) && map == 1)
		temp->valid = 1;
	return (temp->valid);
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
		printf("%d\n", ft_validate(figures[i]));
		i++;
	}
	return (0);
}
