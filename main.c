/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 01:24:37 by olesgedz          #+#    #+#             */
/*   Updated: 2018/12/28 01:50:49 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/includes/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

int main(int argc, char **argv)
{
	char *line;
	int fd;
	argc++;
	fd = open(argv[1], O_RDONLY);
	get_next_line(fd, &line);
	ft_putstr(line);

	return (0);
}
