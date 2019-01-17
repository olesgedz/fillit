/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 16:13:00 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/17 04:14:15 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fillit.h"


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
