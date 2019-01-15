/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:54:51 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/15 16:54:51 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef struct				s_etris
{
	char				**content;
	int 					valid;
	unsigned char		id;
	unsigned char		x;
	unsigned char		y;
	unsigned char		width;
	unsigned char		height;
} t_etris;

typedef struct s_map
{
	char **content;
	int size;
	int nfigures;
} t_map;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;



#endif