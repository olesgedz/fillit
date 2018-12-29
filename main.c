/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 01:24:37 by olesgedz          #+#    #+#             */
/*   Updated: 2018/12/28 21:56:56 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"

void		ft_printmap(char **map)
{
	while (map != NULL)
		ft_putstr(*map++);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	*line;
	char **matrix;
	int i;

	matrix = (char **)(malloc(sizeof(char *) * 4));
	matrix[5] = NULL;
	i = 0;
	if (argc < 2)
	{
		ft_putstr("ERROR");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		matrix[i] = ft_strnew(0);
		matrix[i] = ft_strjoin(matrix[i], line);
		//free(line);
		i++;
		//ft_putstr("\n");
		}

		while (matrix != '\0')
		{
			ft_putstr(*matrix);
			matrix++;
		}
	//ft_printmap(matrix);

	return (0);
}
