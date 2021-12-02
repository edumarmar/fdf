/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edmartin <edmartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:08:00 by edmartin          #+#    #+#             */
/*   Updated: 2021/11/26 17:34:11 by edmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_isocoord	normalize(t_isocoord iso)
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
	int		i;

	i = 0;
	min_x = min_max(iso.x_coord, iso.length, 0);
	max_x = min_max(iso.x_coord, iso.length, 1);
	min_y = min_max(iso.y_coord, iso.length, 0);
	max_y = min_max(iso.y_coord, iso.length, 1);
	while (i <= (iso.length - 1))
	{
		iso.x_coord[i] = 900 * \
		((iso.x_coord[i] - min_x) / (max_x - min_x)) + 50;
		iso.y_coord[i] = 900 * \
		((iso.y_coord[i] - min_y) / (max_y - min_y)) + 50;
		i++;
	}
	return (iso);
}

void	fill_iso(t_isocoord iso, t_map map)
{
	int		i;
	int		j;
	int		count;
	t_coord	cart;

	i = 0;
	count = 0;
	j = 0;
	while (i < map.height)
	{
		while (j < map.width)
		{
			cart.x = j + 1;
			cart.y = i + 1;
			cart.z = 0.15 * map.arr[i][j];
			iso.x_coord[count] = (cart.x * cos(0.523599) + \
			cart.y * cos(2.61799) + cart.z * cos(-1.5708));
			iso.y_coord[count] = (cart.x * sin(0.523599) + \
			cart.y * sin(2.61799) + cart.z * sin(-1.5708));
			count++;
			j++;
		}
		j = 0;
		i++;
	}
}

t_isocoord	calculate_iso(t_map map)
{
	t_isocoord	iso;

	iso.x_coord = malloc(sizeof(float) * map.width * map.height);
	iso.y_coord = malloc(sizeof(float) * map.width * map.height);
	iso.color = map.color;
	iso.length = map.width * map.height;
	fill_iso(iso, map);
	return (iso);
}

float	min_max(float *array, int length, int min_or_max)
{
	float	min_max;
	int		i;

	i = -1;
	min_max = array[0];
	while (++i <= (length - 1))
	{
		if (min_or_max == 0)
		{
			if (array[i] < min_max)
				min_max = array[i];
		}
		else
		{
			if (array[i] > min_max)
				min_max = array[i];
		}
	}
	return (min_max);
}
