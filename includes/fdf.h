/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:22:27 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:22:28 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct s_map
{
	int	**arr;
	int	height;
	int	width;
	int	*color;
}				t_map;

typedef struct s_coord
{
	int		x;
	int		y;
	float	z;
}				t_coord;

typedef struct s_fcoord
{
	float		x;
	float		y;
}				t_fcoord;

typedef struct s_isocoord
{
	float	*x_coord;
	float	*y_coord;
	int		length;
	int		*color;
}				t_isocoord;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_isocoord	iso;
}				t_vars;

void					print_pixel(t_data *img, int x, int y, int color);
void					draw_line(t_data *img, int *xy_o, int *xy_f, int color);
t_isocoord				calculate_iso(t_map map);
float					min_max(float *array, int length, int min_or_max);
t_isocoord				normalize(t_isocoord iso);
int						hex_to_int(char *hex);
int						count_width(char *path);
int						count_height(char *path);
t_map					new_map(char *path);
void					fill_map(t_map map, char *path);
int						*xy_create(int *arr, int x, int y);
void					free_array(char **array);
void					free_map(t_vars *vars);
void					free_origin(int *xy_o, int *xy_f);

#endif
