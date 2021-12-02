/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:07:43 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:07:44 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_up(t_coord dxy, t_fcoord coord, t_data *img, int color)
{
	float	p;
	int		i;

	i = 0;
	p = 2 * abs(dxy.y) - abs(dxy.x);
	while (i < abs(dxy.x))
	{
		if (dxy.x < 0)
			coord.x--;
		else
			coord.x++;
		if (p >= 0)
		{
			if (dxy.y < 0)
				coord.y--;
			else
				coord.y++;
			p = p + 2 * abs(dxy.y) - 2 * abs(dxy.x);
		}
		else
			p = p + 2 * abs(dxy.y);
		print_pixel(img, coord.x, coord.y, color);
		i++;
	}
}

void	draw_down(t_coord dxy, t_fcoord coord, t_data *img, int color)
{
	float	p;
	int		i;

	i = 0;
	p = 2 * abs(dxy.x) - abs(dxy.y);
	while (i < abs(dxy.y))
	{
		if (dxy.y < 0)
			coord.y--;
		else
			coord.y++;
		if (p >= 0)
		{
			if (dxy.x < 0)
				coord.x--;
			else
				coord.x++;
			p = p + 2 * abs(dxy.x) - 2 * abs(dxy.y);
		}
		else
			p = p + 2 * abs(dxy.x);
		print_pixel(img, coord.x, coord.y, color);
		i++;
	}
}

void	draw_line(t_data *img, int *xy_o, int *xy_f, int color)
{
	t_coord		dxy;
	t_fcoord	coord;

	dxy.x = xy_f[0] - xy_o[0];
	dxy.y = xy_f[1] - xy_o[1];
	coord.x = xy_o[0];
	coord.y = xy_o[1];
	if (abs(dxy.x) > abs(dxy.y))
		draw_up(dxy, coord, img, color);
	else
		draw_down(dxy, coord, img, color);
}
