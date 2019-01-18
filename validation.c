/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 03:35:56 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/19 02:31:44 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

/*
**get (0,0) start of figure
*/

int		ft_getsize_y(t_etris *figure)
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

int		ft_getsize_x(t_etris *figure)
{
	int j;
	int k;
	int start;
	int end;

	end = -1;
	start = 5;
	j = -1;
	while (++j < 4)
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
	}
	figure->x = start;
	return (figure->width = end - start + 1);
}

void	ft_count_nieghbors(int j, int k, int *count, char **temp)
{
	if (temp[j][k] == '#')
	{
		if (k + 1 <= 3 && temp[j][k + 1] == '#')
			*count += 1;
		if (j + 1 <= 3 && temp[j + 1][k] == '#')
			*count += 1;
	}
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
	if ((count == 3 || count == 4) && map == 1)
		figure->valid = 1;
	else
		figure->valid = 0;
	return (figure->valid);
}

int		ft_file_valid(t_etris **figures, int number)
{
	int i;

	i = 0;
	while (i < number)
	{
		if (!ft_validate(figures[i]))
			ft_error();
		ft_countsharps(figures[i]);
		ft_getsize_y(figures[i]);
		ft_getsize_x(figures[i]);
		ft_normfigure(figures[i]->content, figures[i]);
		i++;
	}
	return (0);
}
