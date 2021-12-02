/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:07:51 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:52 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color(t_isocoord iso, int i, int is_x, int w)
{
	int	color;

	color = 0xFFFFFF;
	if (is_x)
	{
		if (iso.color[i] != 0)
			color = iso.color[i];
		if (iso.color[i + 1] != 0)
			color = iso.color[i + 1];
	}
	else
	{
		if (iso.color[i] != 0)
			color = iso.color[i];
		if (iso.color[i + w] != 0)
			color = iso.color[i + w];
	}
	return (color);
}

void	draw_iso(t_isocoord iso, t_data img, int h, int w)
{
	int	i;
	int	*xy_o;
	int	*xy_f;

	i = 0;
	xy_o = malloc(sizeof(int) * 2);
	xy_f = malloc(sizeof(int) * 2);
	while (i != (w * h - 1))
	{
		if ((i + 1) <= (w * (h - 1)))
			draw_line(&img, \
			xy_create(xy_o, (int)iso.x_coord[i], (int)iso.y_coord[i]), \
			xy_create(xy_f, (int)iso.x_coord[i + w], (int)iso.y_coord[i + w]), \
			color(iso, i, 0, w));
		if (((i + 1) % w) == 0)
		{
			i++;
			continue ;
		}
		draw_line(&img, xy_create(xy_o, (int)iso.x_coord[i], \
		(int)iso.y_coord[i]), xy_create(xy_f, (int)iso.x_coord[i + 1], \
		(int)iso.y_coord[i + 1]), color(iso, i, 1, w));
		i++;
	}
	free_origin(xy_o, xy_f);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free_map(vars);
		exit(1);
	}
	return (0);
}

void	window_draw(t_map map, t_isocoord iso)
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_data	img;
	t_vars	vars;

	mlx_ptr = mlx_init();
	mlx_window = mlx_new_window(mlx_ptr, 1000, 1000, "Title");
	img.img = mlx_new_image(mlx_ptr, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
	&img.line_length, &img.endian);
	draw_iso(iso, img, map.height, map.width);
	mlx_put_image_to_window(mlx_ptr, mlx_window, img.img, 0, 0);
	vars.mlx = mlx_ptr;
	vars.win = mlx_window;
	vars.map = map;
	vars.iso = iso;
	mlx_key_hook(mlx_window, &key_hook, &vars);
	mlx_loop(mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_isocoord	iso;

	if (argc != 2 || open(argv[1], O_RDONLY) == -1)
		exit(1);
	map = new_map(argv[1]);
	iso = calculate_iso(map);
	iso = normalize(iso);
	window_draw(map, iso);
	return (1);
}
