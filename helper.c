/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 14:59:49 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/19 02:31:05 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>

void		ft_check_end(int *flag, char *end, int fd)
{
	*flag = get_next_line(fd, &end);
	if (end)
		ft_memdel((void **)&end);
}

int			ft_countsharps(t_etris *figure)
{
	short j;
	short k;
	short sharps;

	j = 0;
	sharps = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			if ((figure->content)[j][k] == '#')
				sharps++;
			k++;
		}
		j++;
	}
	if (sharps != 4)
		ft_error();
	return (0);
}
