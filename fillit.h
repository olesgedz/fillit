/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:54:51 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/19 02:31:17 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef struct		s_etris
{
	char			**content;
	int				valid;
	unsigned char	id;
	unsigned char	x;
	unsigned char	y;
	unsigned char	width;
	unsigned char	height;
}					t_etris;

typedef struct		s_map
{
	char			**content;
	int				size;
}					t_map;

void				ft_figures_init(t_etris ***figures);
t_map				*ft_map_init(int n);
void				ft_check_end(int *flag, char *end, int fd);

char				**ft_normfigure(char **dst, t_etris *figure);
int					ft_file_valid(t_etris **figures, int number);
int					ft_readmap(t_etris **figures, int fd);

void				ft_mainloop(t_etris **figures, t_map *map);
void				ft_free_map(t_map *map);
void				ft_free_everything(t_map *map, t_etris **figures);

int					ft_checkwidth(char **figure, int j, int *map);
void				ft_error();
int					ft_checkwidth(char **figure, int j, int *map);
int					ft_countsharps(t_etris *figure);

#endif
